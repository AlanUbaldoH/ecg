class Graf {

  int nX, nY, colF;
  int anteriorXT , anteriorXH;
  float anteriorYT, anteriorYH;
  //boolean primeroT, primeroH;
  Graf (int x, int y, int cF){
    nX = x;
    nY = y; 
    colF  = cF;
  }
  void cuadricula1(){// Temperatura
    fill(0, 0, 0);
    text("ECG", (nX / 2) , 70);
    stroke(150);   
    for (int  j = 60 ; j <= nX - 60; j = j + 20){
      line (j, 80, j, (nY / 2) - 20);      } // Vert
    for (int  j = 80 ; j <= (nY / 2) - 20; j = j + 20){
      line (60, j, nX - 60, j);} // Horiz
    int i = 0;
    for (int n = (nY / 2) - 20; n >= (nY / 2) - 220; n = n - 20){ //modificar valores de cuadricula
      fill(0, 0, 0);
      text(i, 35, n + 5);
      i = i + 5;
      
    }
  }
  
  void cuadricula2(){// Humedad
    fill(0, 0, 0);
    text("SATURACION DE OXIGENO", (nX / 2) , (nY / 2) + 10);
    stroke(150);   
    for (int  j = 60 ; j <= nX - 60; j = j + 20){
      line (j, (nY / 2) + 20 , j, nY - 80);} // Vert
    for (int  j = (nY / 2) + 20 ; j <= nY - 80; j = j + 20){
      line (60, j, nX - 60, j);} // Horiz
    int i = 0;  
    for (int n = nY - 80; n >= nY - 280; n = n - 20){
      fill(0, 0, 0);
      text(i, 35, n + 5);
      i = i + 10;
    }
 
  }
  
  void borra(){
    fill(colF); // Color del fondo
    noStroke();
    rectMode(CORNERS);
    rect(50 , 50, nX , nY  ); 
  }
  
  void puntosT(int x, float tem, boolean primeroT){
      
      float vT =tem/100+50;
      if (primeroT == false){
        stroke(50);
        line(anteriorXT, anteriorYT, x, vT);
        
      
      }
      anteriorXT = x;
      anteriorYT = vT;
        
  }
void puntosH(int x, float hum, boolean primeroH){
            
      float vH =hum/100+50; 
      if (primeroH == false){
        stroke(150);
        line(anteriorXH, anteriorYH, x, vH);
        
      
      }
        anteriorXH = x;
        anteriorYH = vH;   
  }

}
