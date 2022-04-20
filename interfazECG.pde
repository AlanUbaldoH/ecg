import processing.serial.*;

int x = 65, ancho = 800, alto = 700;
int cFondo = 255; //Color fondo
boolean flagTemp = false; 
boolean pH = true;
boolean pT = true;
float t = 100, h = 0 ;
PrintWriter datos;
Serial puertoArduino;
Graf g = new Graf(ancho, alto, cFondo);


void setup (){
 
  size(1000, 800);
  background(255);
  print(Serial.list());//Cambia el indice [1] por el que indique la consola
  puertoArduino = new Serial(this, Serial.list()[2], 9600);
  datos = createWriter("almacenadatos");
  fill(255, 0, 0);
  text("ECG : ", 20, 20);
  fill(0, 0, 255);
  text("SATURACION DE O2 (%) : ", 20, 40);
  pT = true;
  pH = true;
  g.cuadricula1();
  g.cuadricula2();
}

void draw(){

  String inString = puertoArduino.readStringUntil('\n'); 
  if (inString != null){
      
     inString = trim(inString);
     if (flagTemp == false){
      fill(255,255,255);
      noStroke();
      rectMode(CORNERS); 
      rect(140,20,200,45);//Borra lectura anterior 
      h = float(inString);
      datos.print(h +" "+ TAB); 
      flagTemp = true;
      fill (0,0,255);
      text(h, 140, 40);
      println("ecg :", h);
      
        g.puntosH(x, h, pH);
        
        
       pH = false;
     }
     else{
       fill(255,255,255);
       noStroke();
       rectMode(CORNERS);
       rect(140,5,200,25); //borra lectura anterior 
       t = float(inString);
       
       datos.println(t);
       flagTemp = false;
       fill (255,0,0);
       text(t, 140, 20);
       println("Saturacion de oxigeno", t);
          
         g.puntosT(x, t, pT);
          
         pT = false;  
     }
     
     x = x + 5;
     
     }
                
     if (x > ancho - 60) {
        x = 60;
        pT = true;
        pH = true;
        g.borra();
        g.cuadricula1();
        g.cuadricula2();
              
     }
         
    }
     
void keyPressed() {//Presionar 'ESC' para salir
    datos.flush();  
    datos.close();  
    exit();  
}
