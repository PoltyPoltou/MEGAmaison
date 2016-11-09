	#include "Arduino.h"
	#include "Wire.h"


	//address of i2c devices
	byte clockaddress = B01101000;
	byte thermoAddress = B01001000;
	String receivedData;

	void setup(){

		Serial.begin(9600);
		Wire.begin();
		ds1307StartClock(clockaddress);
		ds1307PrintTime();
		tcn75aPrintTemperature();
		Serial.println("Écrivez setup pour accéder aux configurations");

		Serial.println("Écrivez print pour accéder afficher des informations");

	}



	void loop(){
		delay(1000);
	}

	//allows to start the clock for DS1037
	void ds1307StartClock(byte deviceAddress){

		setRegisterIndex(0x00,clockaddress);
		Wire.requestFrom(int(deviceAddress),1);
		while(Wire.available()-1){}
		byte setup= Wire.read();

		if(setup>>7 == 1)
		{
			Wire.beginTransmission(deviceAddress);
			Wire.write(0x00);
			Wire.write(setup & 0x7F);
			Wire.endTransmission();
		}
	}
	//No use
	unsigned int reverseByte(unsigned int sorted, int nbBits){
		unsigned int reversed=0;
		for(int i=0;i<nbBits;i++){
			reversed|=(sorted&(2^i))<<(nbBits-1-i);
		}
		return reversed;
	}

	//print the temperature
	void tcn75aPrintTemperature(){
		float unit,decimal;
		float temp;
		boolean minus;
		setRegisterIndex(thermoAddress,0x00);
		Wire.requestFrom(int(thermoAddress),2);
		while(!Wire.available());
		unit = Wire.read();
		minus=unit>>7;
		unit&=0x7F;
		decimal = Wire.read()>>4;
		temp = unit + decimal/16;
		if(minus)temp = -1*temp;
		Serial.print(temp);
		Serial.println("°C");
	}

	//print the time given by the clock
	void ds1307PrintTime(){
		setRegisterIndex(0x00,clockaddress);
		Wire.requestFrom(int(clockaddress),7);
		delay(100);
		Serial.print(interpretData(Wire.read(),0x7F));
		Serial.print(" secondes ");
		Serial.print(interpretData(Wire.read(),0x7F));
		Serial.print(" minutes ");
		Serial.print(interpretData(Wire.read(),0x3F));
		Serial.print(" heures   ");
		Wire.read();
		Serial.print(interpretData(Wire.read(),0x3F));
		Serial.print("/");
		Serial.print(interpretData(Wire.read(),0x1F));
		Serial.print("/");
		Serial.print(interpretData(Wire.read(),0xFF));
		Serial.println("");
	}
	//set the register pointer
	void setRegisterIndex(byte pointer, byte deviceAddress){

		Wire.beginTransmission(deviceAddress);
		Wire.write(pointer);
		Wire.endTransmission();
	}

	//set a register
	void setRegisterData(byte pointer, byte deviceAddress, byte data){

			Wire.beginTransmission(deviceAddress);
			Wire.write(pointer);
			Wire.write(data);
			Wire.endTransmission();
		}

	//keep interest of the data and convert it
	int interpretData(byte data,byte cache){

		data = data&cache;
		return convertDatatoNum(data);
	}

	//convert weird byte to normal base 10
	int convertDatatoNum(byte data){

		//4 higher bits are corresponding to the tens
		//4 lowers are the units
		return (data>>4)*10+(data&0x0F);
	}

	//convert normal base 10 to weird byte
	byte convertNumtoData(unsigned int num){

		byte unit =num%10;
		byte tens =(num-unit)/10;
		return (tens<<4)+unit;

	}

	int charToDec(char c){
		return c-48; //ASCII table numbers begin at n°48 (0)
	}

	void serialEvent(){
		while(Serial.available()){
			receivedData = Serial.readStringUntil('\n');
			//enter the setup
			if(receivedData == "setup")setups();
			if(receivedData == "print")prints();
		}
	}


	void setups(){
		Serial.println("Vous êtes dans les réglages. Options : clock, thermo, done (pour sortir)");
		while(receivedData!="done"){
			receivedData = Serial.readStringUntil('\n');
			if(receivedData=="clock"){
				setupHorloge();
			}
			if(receivedData=="thermo"){
				setupThermo();
			}
		}
	}

	void prints(){
		Serial.println("Que voulez vous afficher? Options : clock, thermo, done (pour sortir)");
		while(receivedData!="done"){
			receivedData = Serial.readStringUntil('\n');
			if(receivedData=="clock"){
				ds1307PrintTime();
			}

			if(receivedData=="clock"){
				tcn75aPrintTemperature();
			}
		}
	}

	void setupThermo(){

		Serial.println("REGLAGE DU THERMOMETRE");
		setRegisterIndex(0x01, thermoAddress);
		Wire.requestFrom(int(thermoAddress),1);
		while(!Wire.available()){}
		Serial.println("Réglage actuel");
		Serial.println(Wire.read(),BIN);
	}

	void setupHorloge(){

		boolean end= false;
		int setupInt=-1;
		int config=0;
		char buffer[8];
		boolean stop;
		Serial.println("REGLAGE DE L'HEURE");
		while(!end){

			String setup = Serial.readStringUntil('\n');

			if(setup=="sec")setupInt=0;
			else if(setup=="min")setupInt=1;
			else if(setup=="h")setupInt=2;
			else if(setup=="jour")setupInt=3;
			else if(setup=="date")setupInt=4;
			else if(setup=="mois")setupInt=5;
			else if(setup=="année")setupInt=6;
			else if(setup=="regsitre")setupInt=7;
			else setupInt=-1;
			stop = false;
			if(setup=="done")end=true;
			else{
				switch(setupInt){
					case 0: //secondes
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<10&&charToDec(buffer[0])>=0)
								{
									setRegisterData(0x00,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<=9&&charToDec(buffer[1])>=0)
								{
									setRegisterData(0x00,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}
						break;

					case 1: //minutes
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,5);
							if(config==1){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0)
								{
									setRegisterData(0x01,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<=9&&charToDec(buffer[1])>=0)
								{
									setRegisterData(0x01,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}
						break;
					case 2: //heures
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0)
								{
									setRegisterData(0x02,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=2&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<10&&charToDec(buffer[1])>=0&&((charToDec(buffer[0]))*10+charToDec(buffer[1]))<24)
								{
									setRegisterData(0x02,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}

						break;
					case 3://jour(lundi...)
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<=7&&charToDec(buffer[0])>=1)
								{
									setRegisterData(0x03,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}
						break;

					case 4://date(10...)
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=1)
								{
									setRegisterData(0x04,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=3&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<=9&&charToDec(buffer[1])>=1&&((charToDec(buffer[0]))*10+charToDec(buffer[1]))<=31)
								{
									setRegisterData(0x04,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}
						break;

					case 5://mois
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0)
								{
									setRegisterData(0x05,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=1&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<=9&&charToDec(buffer[1])>=1&&(charToDec(buffer[0]))*10+charToDec(buffer[1])<=12)
								{
									setRegisterData(0x05,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
								else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
									stop=true;
								}
							}
						}
						break;

					case 6://année
						while(!stop){
							delay(1000);

							config = Serial.readBytesUntil('\n',buffer,4);
							if(config==1){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0)
								{
									setRegisterData(0x06,clockaddress,convertNumtoData(charToDec(buffer[0])));
									stop=true;
								}
							}
							else if(config==2){
								if(charToDec(buffer[0])<=9&&charToDec(buffer[0])>=0&&charToDec(buffer[1])<=9&&charToDec(buffer[1])>=0)
								{
									setRegisterData(0x06,clockaddress,convertNumtoData((charToDec(buffer[0]))*10+charToDec(buffer[1])));
									stop=true;
								}
							}
							else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
								stop=true;
							}
						}
						break;
					case 7:
						config = Serial.readBytesUntil('\n',buffer,8);
						if(config==1){

						}
						else if(config==4&&buffer[0]=='b'&&buffer[1]=='a'&&buffer[2]=='c'&&buffer[3]=='k'){
							stop=true;
						}
						break;

					default:
						Serial.println("Parametrez toutes les données écrire \"done\" entrées possibles: sec, min, h, jour, date, mois, année, registre");
						break;
				}
			}
		}
		end = false;
	}












