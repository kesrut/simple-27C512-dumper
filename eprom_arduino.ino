/*
Simple M27C512 EPROM Reader
*/

#define CE 52
#define OE 53
#define ADDR_START 22
#define DATA_START 40
#define BYTE_COUNT 65536
#define ADDR_BUS_SIZE 16
#define DATA_BUS_SIZE 8

void setup()
{
   Serial.begin(9600) ; 
   pinMode(CE, OUTPUT) ; 
   pinMode(OE, OUTPUT) ; 
   digitalWrite(CE, LOW) ;
   digitalWrite(OE, LOW) ;
   int i=0 ; 
   for (i=ADDR_START; i < ADDR_START+ADDR_BUS_SIZE; i++) 
   {
      pinMode(i, OUTPUT) ; 
   }
   for (i=DATA_START; i < DATA_START+DATA_BUS_SIZE; i++)
   {
     pinMode(i, INPUT) ;
   }
 
}
unsigned long addr = 0; 

void loop()
{  
  if (Serial.available())
  {
    byte incoming = Serial.read() ; 
    if (incoming == 0xff)
    {
      while (addr < BYTE_COUNT)
      {
        unsigned long i=0; 
        unsigned long k=1; 
        for (i=0; i < ADDR_BUS_SIZE; i++)
        {
          byte bit_value = (addr & k) >> i;
          digitalWrite(ADDR_START+i, bit_value) ; 
          k = k << 1; 
        }
        delay(5) ; 
        k = 1 ; 
        int data_value = 0 ; 
        for (i=0; i < DATA_BUS_SIZE; i++)
        {
          byte bit_value = digitalRead(DATA_START+i) ;  
          data_value = (data_value | (bit_value << i)) ; 
          k = k << 1 ; 
        }
        Serial.write(data_value) ; 
        addr++ ; 
       }
    }
  }
}
