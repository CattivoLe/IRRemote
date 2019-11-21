#include <EtherCard.h>
#include <IRremote.h>
 
static byte mymac[] = { 0x5e,0xf7,0x69,0xc5,0x6b,0xd3 };
static byte myip[] = { 10,40,0,221 };
static byte gwip[] = { 10,40,0,1 };
 
const char website[] PROGMEM = "10,40,0,221";
byte Ethernet::buffer[500];
 
BufferFiller bfill;

IRsend irsend;
 
void setup () { 
 ether.begin(sizeof Ethernet::buffer, mymac, 10);
 ether.staticSetup(myip);
}
 
void loop () {
  
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
 
 if (pos){
 char *data = (char *) Ethernet::buffer + pos;

 if (strstr(data, "?POWER")){irsend.sendNEC(0x404050AF, 32);}
 if (strstr(data, "?CHAN=UP")){irsend.sendNEC(0x4040A857, 32);}
 if (strstr(data, "?CHAN=DOWN")){irsend.sendNEC(0x404018E7, 32);}
 if (strstr(data, "?VOL=UP")){irsend.sendNEC(0x4040827D, 32);}
 if (strstr(data, "?VOL=DOWN")){irsend.sendNEC(0x404042BD, 32);}
 if (strstr(data, "?MENU")){irsend.sendNEC(0x40406897, 32);}

 if (strstr(data, "?OKEY")){irsend.sendNEC(0x4040B04F, 32);}
 if (strstr(data, "?LEFT")){irsend.sendNEC(0x40408877, 32);}
 if (strstr(data, "?RIGHT")){irsend.sendNEC(0x404008F7, 32);}
 if (strstr(data, "?UP")){irsend.sendNEC(0x4040D02F, 32);}
 if (strstr(data, "?DOWN")){irsend.sendNEC(0x4040708F, 32);}

 
 bfill = ether.tcpOffset();
 bfill.emit_p(PSTR(
 "HTTP/1.0 200 OK\r\n"
 "Content-Type: text/html\r\n"
 "\r\n"
 
 "<meta charset='UTF-8'>"
 

 "<head><title>"
  "Digital October HTB+</title>"
 "</title></head>"
 
 "<title>Digital October</title>" 

 "<h3>Digital October HTB+ Remote Control</h3>"

 
 "<p>Channel Control&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Volume Control</p>"

 "<a href='/?CHAN=DOWN'>Prev</a>&nbsp;&nbsp;&nbsp;"
 "<a href='/?CHAN=UP'>Next</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  "
 "<a href='/?VOL=DOWN'>Down</a>&nbsp;&nbsp;&nbsp;"
 "<a href='/?VOL=UP'>Up</a>"

 "<p></p>"
 
 "<a href='/?POWER'>Power</a>&nbsp;"


 //"<a href='/?OKEY'>OK</a>&nbsp;"

 //"<a href='/?LEFT'>Left</a>&nbsp;"
 //"<a href='/?RIGHT'>Right</a>&nbsp;"
 //"<a href='/?UP'>Up</a>&nbsp;"
 //"<a href='/?DOWN'>Down</a>&nbsp;"

 //"<a href='/?MENU'>Menu</a>&nbsp;"
 
 ));
 ether.httpServerReply(bfill.position());
 }
}

//"<img src='http://digitaloctober.ru/assets/design_2012/new_logo.png'/>"
//"<style>a{color:#3D94D7;display:block;margin:20px;}</style>"





