#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

GLfloat test=0.1;
//to manage which scene to be displayed
int state=0,cx=0;
//to manage window position
int x,y,i,colorindex=0;
//manage tyre
float tx=0;
//crashing flag
int isCrashed=0;
//aeroplane movement
int dpx=-500,dpy=0;
//mamage day and night
const GLfloat color[10][3]={
  {0.0,0.03,0.08},
  {0.01,0.07,0.16},
  {0.02,0.11,0.27},
  {0.02,0.16,0.39},
  {0.05,0.22,0.49},
  {0.07,0.28,0.6},
  {0.13,0.35,0.69},
  {0.5294117647,0.8078431373,0.9215686275},
  {0.23,0.45,0.79},
  {0.39,0.64,0.87}
};

//scene1 variables
float speed=2,startx=2,starty=-200,flag=0;

//font types
void *fonts[]=
{
  GLUT_BITMAP_9_BY_15,
  GLUT_BITMAP_TIMES_ROMAN_10,
  GLUT_BITMAP_TIMES_ROMAN_24,
  GLUT_BITMAP_HELVETICA_18,
  GLUT_BITMAP_HELVETICA_12
};

//GL_init function
void init()
{
	glClearColor(1,1,1,1);
  glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1000,0,1000);
  glMatrixMode(GL_MODELVIEW);
}

//method to handle keyboard inputs keyboard-
void keyboard( unsigned char key, int x, int y )
{
  //handle --> press any key to continue
  if(state==0){
     state=1;

  }

  //move to end
  if(state==5){
      state=6;
  }

}

//function to write text
void write_text(int x, int y, char *string,void *font)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

//with default font
void renderBitmapString(float x, float y, const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

//blast polygon construction
void blast()
  {
    glPushMatrix();
    glTranslated(-10.0, -60.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(404.4, 320.0);
    glVertex2f(384.0, 285.0);
    glVertex2f(368.0, 344.5);
    glVertex2f(344.0, 355.0);
    glVertex2f(347.2, 414.5);
    glVertex2f(332.8, 442.5);
    glVertex2f(347.2, 477.5);
    glVertex2f(352.0, 530.0);
    glVertex2f(379.2, 519.5);
    glVertex2f(396.8, 565.0);
    glVertex2f(416.0, 530.0);
    glVertex2f(440.0, 547.5);
    glVertex2f(452.8, 512.5);
    glVertex2f(472.0, 512.5);
    glVertex2f(475.2, 470.5);
    glVertex2f(488.0, 442.5);
    glVertex2f(488.0, 404.0);
    glVertex2f(470.0, 372.5);
    glVertex2f(475.2, 337.5);
    glVertex2f(464.0, 306.0);
    glVertex2f(444.8, 320.0);
    glVertex2f(425.6, 285.0);
    glVertex2f(404.8, 320.0);
    glEnd();
    glPopMatrix();
  }

//intro --scene1 display
void intro()
{
        glColor3f(0.5,0.2,0.6);
        write_text(300,130," SAHYADRI COLLEGE OF ENGINEERING AND MANAGEMENT",fonts[3]);
        glColor3f(0.3,0.5,0.8);
        write_text(375,100,"DEPT. OF COMPUTER SCIENCE & ENGG.",fonts[0]);
        glColor3f(0.8,0.1,0.2);
        write_text(300,600,"GRAPHICAL IMPLEMENTATION OF AIRPLANE CRASH",fonts[2]);
        glColor3f(1.0,0.0,1.0);
        write_text(450,500,"SUBMITTED BY :",fonts[0]);
        glColor3f(0.3,0.5,0.8);
        write_text(225,450,"NISHAN B",fonts[3]);
        write_text(670,450,"PRATHEEKSHA S KARANDOOR",fonts[3]);
        write_text(180,300,"",fonts[3]);
        write_text(220,400,"(4SF15CS097)",fonts[0]);
        write_text(680,400,"(4SF15CS109)",fonts[0]);

        write_text(380,200,"[ PRESS ANY KEY TO CONTINUE ]",fonts[3]);
}

//fuction to draw draw circle
void drawfcircle(GLfloat x,GLfloat y,GLfloat radius){
	int i;
	int triangleAmount=200000;
	GLfloat twicePi=2.0f*3.141592653;
	glEnable(GL_POINTS);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for(i=0;i<=triangleAmount;i++){
		glVertex2f(x,y);
		glVertex2f(x+(radius*cos(i*twicePi/triangleAmount)),y+(radius*sin(i*twicePi/triangleAmount)));
	}
	glEnd();
}

//helper function for drawing sphere
void sphere(float r, float g, float b, float a)
{
        glColor4f(r,g,b,a);
        glutSolidSphere(1,100,32);

}

//fuction to draw clouds
void drawClouds(){
  glColor3f(0.9,0.9,0.9);

  glPushMatrix();
  glTranslatef(530,750,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(580,740,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(580,700,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(500,8000,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

}

//function to draw airoplane tire
void drawTyre(){
  glColor3f(0.1,0.1,0.1);
  glutSolidSphere(3,32,32);

  //holder
  glColor3f(0.13, 0.13, 0.13);
  glBegin(GL_POLYGON);
  glVertex2f(425,675);
  glVertex2f(575,675);
  glVertex2f(575,665);
  glVertex2f(550,650);
  glVertex2f(450,650);
  glVertex2f(425,665);
  glEnd();

  //tyre rod
  glColor3f(0.46, 0.46, 0.46);
  glBegin(GL_POLYGON);
  glVertex2f(520,660);
  glVertex2f(520,550);
  glVertex2f(480,550);
  glVertex2f(480,660);
  glEnd();


  glColor3f(0.25,0.25,0.25);
  //glutSolidSphere(3,32,32);
  glPushMatrix();
  glTranslatef(500,550,0);
  glScalef(50,50,1);
  glutSolidSphere(1,500,4);
  glPopMatrix();

  glColor3f(1,1,1);
  glPushMatrix();
  glTranslatef(500,550,0);
  glScalef(30,30,1);
  glutWireSphere(1,500,4);
  glPopMatrix();


}

//function to draw sky
void sky()
{
	glColor3f(0.5294117647,0.8078431373,0.9215686275);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,1000);
	glVertex2f(0,1000);
    	glEnd();
}

//fucntion to draw cloud
void cloud()
{
        glPushMatrix();
        glScalef(1.5,1,1.25);
        glTranslatef(0,12,0);
        sphere(1,1,1,0.9);
        glPopMatrix();

        glPushMatrix();
        glScalef(1.5,1,1.25);
        glTranslatef(0,5,3);
        sphere(1,1,1,0.9);
        glPopMatrix();

        glPushMatrix();
        glScalef(1.5,1,1.25);
        glTranslatef(4,7,0);
        sphere(1,1,1,0.9);
        glPopMatrix();

        glPushMatrix();
        glScalef(1.5,1,1.25);
        glTranslatef(-4,7,0);
        sphere(1,1,1,0.9);
        glPopMatrix();

        glPushMatrix();
        glScalef(2,1.5,2);
        glTranslatef(0,5,0);
        sphere(1,1,1,0.5);
        glPopMatrix();

			}

//method to draw the grid
void drawGrid(){

  glBegin(GL_LINES);
  glColor3f(0,1,0);
  int i;
  for( i=0;i<1000;i+=10){
    glVertex2f(i,0);
    glVertex2f(i,1000);
    glVertex2f(0,i);
    glVertex2f(1000,i);
  }
    glColor3f(1,0,0);
    glVertex2f(0,500);
    glVertex2f(1000,500);
    glVertex2f(500,0);
    glVertex2f(500,1000);
    glEnd();
}

//function to draw aeroplane
void drawAeroplane(){
  //aeroplane front-cone
  glColor3f(0.95,0.95,0.95);
  glBegin(GL_POLYGON);
  glVertex2f(825,700);
  glVertex2f(850,700);
  glVertex2f(940,665);
  glVertex2f(975,600);
  glVertex2f(940,575);
  glVertex2f(860,550);
  glVertex2f(825,550);
  glEnd();

  //glColor3f(1,1,0);
  glPushMatrix();
  glScalef(50,40,0);
  glTranslatef(18.6,15.4,0);
  glutSolidSphere(1,100,100);
  glPopMatrix();

  glPushMatrix();
  glScalef(50,40,0);
  glTranslatef(18.4,15.7,0);
  glutSolidSphere(1,100,100);
  glPopMatrix();

  //airoplane middle
  glColor3f(0.95,0.95,0.95);
  glBegin(GL_POLYGON);
  glVertex2f(825,550);
  glVertex2f(250,550);
  glVertex2f(225,675);
  glVertex2f(450,700);
  glVertex2f(825,700);
  glEnd();

  //aeroplane end
  glColor3f(0.98,0.98,0.98);
  glBegin(GL_POLYGON);
  glVertex2f(250,550);
  glVertex2f(105,615);
  glVertex2f(35,880);
  glVertex2f(95,865);
  glVertex2f(225,675);
  glEnd();

  //aeroplane end wing
  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(35,880);
  glVertex2f(75,870);
  glVertex2f(135,690);
  glVertex2f(105,615);
  glEnd();

  //aeroplane door
  glColor3f(0.43921569, 0.43921569, 0.43921569);
  glBegin(GL_POLYGON);
  glVertex2f(910,600);
  glVertex2f(895,645);
  glVertex2f(840,665);
  glVertex2f(840,600);
  glEnd();

  //Aeroplane Windows
  glColor3f(0.35686275, 0.35686275, 0.35686275);
    int tl=250,tu=300;
    for(i=0;i<8;i++){
      glBegin(GL_POLYGON);
        glVertex2f(tl+=40,600);
        glVertex2f(tl,650);
        glVertex2f(tu+=40,650);
        glVertex2f(tu,600);
      glEnd();
      tl+=20;
      tu+=20;
  }

  //Aeroplane Front and backdoor
  glBegin(GL_POLYGON);
  glVertex2f(750+15,600);
  glVertex2f(750+15,675);
  glVertex2f(800+15,675);
  glVertex2f(800+15,600);
  glEnd();

  //aeroplane wings
  glColor3f(0.91, 0.9, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(450,580);
  glVertex2f(570,580);
  glVertex2f(400,425);
  glVertex2f(320,415);
  glEnd();
  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(350,420);
  glVertex2f(450,525);
  glVertex2f(415,540);
  glVertex2f(320,416);
  glEnd();
  glFlush();

  glColor3f(0.91, 0.9, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(500,700);
  glVertex2f(370,885);
  glVertex2f(360,870);
  glVertex2f(415,695);
  glEnd();


  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(370,885);
  glVertex2f(365,880);
  glVertex2f(460,700);
  glVertex2f(500,700);

  glEnd();

  renderBitmapString(500,660,"AIR INDIA EXPRESS");

  glFlush();

}

//function to draw building
void drawBuilding(){
  //building main-l1
  glColor3f(0.18823529, 0.18823529, 0.18431373);
  glLineWidth(2);
  glBegin(GL_LINE_LOOP);
  glVertex2f(250,500);
  glVertex2f(250,750);
  glVertex2f(600,750);
  glVertex2f(600,500);
  glEnd();
  glLineWidth(1);

  glColor3f(0.92941176, 0.90196078, 0.68627451);
  glBegin(GL_POLYGON);
  glVertex2f(250,500);
  glVertex2f(250,750);
  glVertex2f(600,750);
  glVertex2f(600,500);
  glEnd();

  //building main-l2
  glColor3f(0.29803922, 0.29803922, 0.29803922);
  glBegin(GL_POLYGON);
  glVertex2f(300,750);
  glVertex2f(300,900);
  glVertex2f(550,900);
  glVertex2f(550,750);
  glEnd();

  //building main-l3
  glBegin(GL_POLYGON);
  glColor3f(0.92941176, 0.90196078, 0.68627451);
  glVertex2f(250,800);
  glVertex2f(250,850);
  glVertex2f(600,850);
  glVertex2f(600,800);
  glEnd();


}

//fucntion to draw build-connection
void drawBuildingPath(){

  glColor3f(0.18823529, 0.18823529, 0.18431373);
  glLineWidth(2);
  glBegin(GL_LINE_LOOP);
  glVertex2f(250,600);
  glVertex2f(250,725);
  glVertex2f(0,725);
  glVertex2f(0,600);
  glEnd();
  glLineWidth(1);

  glColor3f(0.92941176, 0.90196078, 0.68627451);
  glBegin(GL_POLYGON);
  glVertex2f(250,600);
  glVertex2f(250,725);
  glVertex2f(0,725);
  glVertex2f(0,600);
  glEnd();


}

//function to draw runway strip
void drawStrip(){
  glColor3f(1,1,1);
  int tx=100,ty=200;
  for(i=0;i<10;i++){
    glBegin(GL_POLYGON);
    glVertex2f(tx+=30,250);
    glVertex2f(tx,300);
    glVertex2f(ty+=30,300);
    glVertex2f(ty,250);
    glEnd();
    tx+=100;
    ty+=100;
  }
}

//function to draw runway
void drawRunWay(){
  glColor3f(0.12941176, 0.12941176, 0.12941176);
  glBegin(GL_POLYGON);
  glVertex2f(0,150);
  glVertex2f(0,450);
  glVertex2f(1000,450);
  glVertex2f(1000,150);
  glEnd();

  glPushMatrix();
  glTranslatef(-120,20,0);
  drawStrip();
  glPopMatrix();

  glPushMatrix();
  glScalef(2,0.5,1);
  glTranslatef(-120,600,0);
  drawStrip();
  glPopMatrix();

  glPushMatrix();
  glScalef(2,0.5,1);
  glTranslatef(-120,50,0);
  drawStrip();
  glPopMatrix();

}

//fucntion to draw Tree
void drawTree(){
  glBegin(GL_POLYGON);
	glColor3f(0.6,0,0);
	glVertex2f(525,500);
	glVertex2f(550,500);
	glVertex2f(550,750);
	glVertex2f(525,750);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6,0,0);
	glVertex2f(550,525);
	glVertex2f(600,575);
	glVertex2f(600,600);
	glVertex2f(550,550);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6,0,0);
	glVertex2f(525,600);
	glVertex2f(525,625);
	glVertex2f(475,675);
	glVertex2f(475,650);
	glEnd();

  // right green
	glColor3f(0,1,0);

  glPushMatrix();
  glTranslatef(620,580,0);
  glScalef(40,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(450,680,0);
  glScalef(40,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(530,750,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(580,740,0);
  glScalef(60,50,0);
  glutSolidSphere(1,100,10);
  glPopMatrix();

}

//fucntion to draw night sky
void darksky()
{
	glColor3f(0.0, 0.03, 0.08);
	glBegin(GL_POLYGON);
  glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,1000);
	glVertex2f(0,1000);
  glEnd();

}

//to draw the sky
void star()
{

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(630,530);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(0.701,0,0);
	glVertex2f(300,800);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(500,500);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(0.501,0.623,1);
	glVertex2f(900,200);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(200,200);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(0.701,0,0);
	glVertex2f(800,700);
	glEnd();glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(100,100);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,0.4,0.63921);
	glVertex2f(200,300);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(0.701,0,0);
	glVertex2f(600,100);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(900,700);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,10.701);
	glVertex2f(900,200);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(900,-300);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,10.701);
	glVertex2f(600,500);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,0.4,0.63921);
	glVertex2f(800,700);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(200,300);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(700,400);
	glEnd();
	glBegin(GL_POINTS);
	glColor3f(1,1,10.701);
	glVertex2f(0,800);
	glEnd();
}

//create 3 tires
void drawLandingGear(){
  glPushMatrix();
  glScalef(0.35,0.35,1);
  glTranslatef(1700,900,0);
  drawTyre();
  glPopMatrix();


  glPushMatrix();
  glScalef(0.35,0.35,1);
  glTranslatef(900,900,0);
  drawTyre();
  glPopMatrix();

  glPushMatrix();
  glScalef(0.35,0.35,1);
  glTranslatef(1000,900,0);
  drawTyre();
  glPopMatrix();
}

//function to draw dubai scene
void drawDubaliAirPort(){
  glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,50);
	glVertex2f(0,50);
	glEnd();

	//runway
	glBegin(GL_POLYGON);
	glColor3f(0.37,0.37,0.37);
	glVertex2f(0,50);
	glVertex2f(1000,50);
	glVertex2f(1000,400);
	glVertex2f(0,400);
	glEnd();

	//above the runway
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(0,400);
	glVertex2f(1000,400);
	glVertex2f(1000,450);
	glVertex2f(0,450);
	glEnd();

	//lawns above the road
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(1000,450);
	glVertex2f(1000,500);
	glVertex2f(0,500);
	glVertex2f(0,450);
	glEnd();

	//airport
	glBegin(GL_POLYGON);
	glColor3f(1,0.98,0.9);
	glVertex2f(250,500);
	glVertex2f(250,750);
	glVertex2f(600,750);
	glVertex2f(600,500);
	glEnd();

	//airport door outline
	glBegin(GL_POLYGON);
	glColor3f(1,0.4,0.4);
	glVertex2f(330,500);
	glVertex2f(330,570);
	glVertex2f(520,570);
	glVertex2f(520,500);
	glEnd();

	//airport left door
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(350,500);
	glVertex2f(350,550);
	glVertex2f(420,550);
	glVertex2f(420,500);
	glEnd();

	//airport right door
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(430,500);
	glVertex2f(430,550);
	glVertex2f(500,550);
	glVertex2f(500,500);
	glEnd();

	//airport windows
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(275,600);
	glVertex2f(275,650);
	glVertex2f(325,650);
	glVertex2f(325,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(350,600);
	glVertex2f(350,650);
	glVertex2f(400,650);
	glVertex2f(400,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(425,600);
	glVertex2f(425,650);
	glVertex2f(475,650);
	glVertex2f(475,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(500,600);
	glVertex2f(500,650);
	glVertex2f(550,650);
	glVertex2f(550,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(275,675);
	glVertex2f(275,725);
	glVertex2f(325,725);
	glVertex2f(325,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(350,675);
	glVertex2f(350,725);
	glVertex2f(400,725);
	glVertex2f(400,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(425,675);
	glVertex2f(425,725);
	glVertex2f(475,725);
	glVertex2f(475,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(500,675);
	glVertex2f(500,725);
	glVertex2f(550,725);
	glVertex2f(550,675);
	glEnd();

 	//grey airpot
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(300,750);
	glVertex2f(300,775);
	glVertex2f(550,775);
	glVertex2f(550,750);
	glEnd();

	//above grey airport

	glBegin(GL_POLYGON);
	glColor3f(1,0.98,0.9);
	glVertex2f(250,775);
	glVertex2f(250,850);
	glVertex2f(600,850);
	glVertex2f(600,775);
	glEnd();
	glColor3f(1,0,0);
	renderBitmapString(275,800,"DUBAI INTERNATIONAL AIRPORT");

	//above airport heading
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(300,850);
	glVertex2f(300,900);
	glVertex2f(550,900);
	glVertex2f(550,850);
	glEnd();

	//flag
	glBegin(GL_POLYGON);
	glColor3f(0.6,0,0);
	glVertex2f(425,900);
	glVertex2f(425,975);
	glVertex2f(435,975);
	glVertex2f(435,900);
	glEnd();

	//greem
	glBegin(GL_POLYGON);
	glColor3f(0,0.6,0);
	glVertex2f(435,975);
	glVertex2f(490,975);
	glVertex2f(490,960);
	glVertex2f(435,960);
	glEnd();

	//white
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2f(435,960);
	glVertex2f(490,960);
	glVertex2f(490,945);
	glVertex2f(435,945);
	glEnd();


	//black
	glBegin(GL_POLYGON);
	glColor3f(0,0,0);
	glVertex2f(435,945);
	glVertex2f(490,945);
	glVertex2f(490,930);
	glVertex2f(435,930);
	glEnd();

	//red
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(435,975);
	glVertex2f(445,975);
	glVertex2f(445,930);
	glVertex2f(435,930);
	glEnd();

	//airport extension
	glBegin(GL_POLYGON);
	glColor3f(0.96,0.96,0.86);
	glVertex2f(250,525);
	glVertex2f(0,525);
	glVertex2f(0,700);
	glVertex2f(250,700);
	glEnd();

	//airport extension window
	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(225,625);
	glVertex2f(175,625);
	glVertex2f(175,675);
	glVertex2f(225,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(150,625);
	glVertex2f(100,625);
	glVertex2f(100,675);
	glVertex2f(150,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(75,625);
	glVertex2f(25,625);
	glVertex2f(25,675);
	glVertex2f(75,675);
	glEnd();

	//green below airport extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(250,500);
	glVertex2f(0,500);
	glVertex2f(0,525);
	glVertex2f(250,525);
	glEnd();

	//airport teal extension
	glBegin(GL_POLYGON);
	glColor3f(0.56,0.73,0.56);
	glVertex2f(250,615);
	glVertex2f(0,615);
	glVertex2f(0,525);
	glVertex2f(250,525);
	glEnd();

	//lawn left extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(600,500);
	glVertex2f(600,550);
	glVertex2f(850,550);
	glVertex2f(875,525);
	glVertex2f(875,515);
	glVertex2f(850,500);
	glEnd();

	//left lawn
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(750,500);
	glVertex2f(775,550);
	glVertex2f(1000,550);
	glVertex2f(1000,500);
	glEnd();

  glPushMatrix();
  glTranslatef(400,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glScalef(0.8,0.8,1);
  glTranslatef(350,100,0);
  drawTree();
  glPopMatrix();


}

//fucntion to draw indian AIRPORT
void drawIndianAirport(){
  //below the runway
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,50);
	glVertex2f(0,50);
	glEnd();

	//runway
	glBegin(GL_POLYGON);
	glColor3f(0.37,0.37,0.37);
	glVertex2f(0,50);
	glVertex2f(1000,50);
	glVertex2f(1000,400);
	glVertex2f(0,400);
	glEnd();

	//above the runway
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(0,400);
	glVertex2f(1000,400);
	glVertex2f(1000,450);
	glVertex2f(0,450);
	glEnd();

	//lawns above the road
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(1000,450);
	glVertex2f(1000,500);
	glVertex2f(0,500);
	glVertex2f(0,450);
	glEnd();

	//airport
	glBegin(GL_POLYGON);
	glColor3f(1,0.98,0.9);
	glVertex2f(400,500);
	glVertex2f(400,750);
	glVertex2f(750,750);
	glVertex2f(750,500);
	glEnd();

	//airport door outline
	glBegin(GL_POLYGON);
	glColor3f(1,0.4,0.4);
	glVertex2f(465,500);
	glVertex2f(465,585);
	glVertex2f(685,585);
	glVertex2f(685,500);
	glEnd();

	//airport left door
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(475,500);
	glVertex2f(475,575);
	glVertex2f(570,575);
	glVertex2f(570,500);
	glEnd();

	//airport right door
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(675,500);
	glVertex2f(675,575);
	glVertex2f(580,575);
	glVertex2f(580,500);
	glEnd();

	//airport windows
	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(425,600);
	glVertex2f(425,650);
	glVertex2f(475,650);
	glVertex2f(475,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(500,600);
	glVertex2f(500,650);
	glVertex2f(550,650);
	glVertex2f(550,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(575,600);
	glVertex2f(575,650);
	glVertex2f(625,650);
	glVertex2f(625,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(650,600);
	glVertex2f(650,650);
	glVertex2f(700,650);
	glVertex2f(700,600);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(425,675);
	glVertex2f(425,725);
	glVertex2f(475,725);
	glVertex2f(475,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(500,675);
	glVertex2f(500,725);
	glVertex2f(550,725);
	glVertex2f(550,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(575,675);
	glVertex2f(575,725);
	glVertex2f(625,725);
	glVertex2f(625,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0,1);
	glVertex2f(650,675);
	glVertex2f(650,725);
	glVertex2f(700,725);
	glVertex2f(700,675);
	glEnd();

	//grey airpot
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(425,750);
	glVertex2f(425,775);
	glVertex2f(725,775);
	glVertex2f(725,750);
	glEnd();

	//above grey airport

	glBegin(GL_POLYGON);
	glColor3f(1,0.98,0.9);
	glVertex2f(400,775);
	glVertex2f(400,850);
	glVertex2f(750,850);
	glVertex2f(750,775);
	glEnd();
	glColor3f(1,0,0);
	renderBitmapString(405,800,"MANGLORE INTERNATIONAL AIRPORT");

	//above airport heading
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(425,850);
	glVertex2f(425,900);
	glVertex2f(725,900);
	glVertex2f(725,850);
	glEnd();

	//flag
	glBegin(GL_POLYGON);
	glColor3f(0.6,0,0);
	glVertex2f(560,900);
	glVertex2f(560,975);
	glVertex2f(568,975);
	glVertex2f(568,900);
	glEnd();

	//saffron
	glBegin(GL_POLYGON);
	glColor3f(1,0.5,0);
	glVertex2f(568,975);
	glVertex2f(625,975);
	glVertex2f(625,960);
	glVertex2f(568,960);
	glEnd();

	//white
	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2f(568,960);
	glVertex2f(625,960);
	glVertex2f(625,945);
	glVertex2f(568,945);
	glEnd();
	glColor3f(0,0,1);
	drawfcircle(596.5,952.5,8);

  //ashokachakra
  //glPushMatrix();
	//glColor3f(0,0,1);
	//glutSolidSphere(15,24,4);
	//glTranslatef(569.5,952.5,0);
	//glPopMatrix();

	//green
	glBegin(GL_POLYGON);
	glColor3f(0,0.6,0);
	glVertex2f(568,945);
	glVertex2f(625,945);
	glVertex2f(625,930);
	glVertex2f(568,930);
	glEnd();

	//airport extension
	glBegin(GL_POLYGON);
	glColor3f(0.96,0.96,0.86);
	glVertex2f(750,525);
	glVertex2f(1000,525);
	glVertex2f(1000,700);
	glVertex2f(750,700);
	glEnd();

	//airport extension window
	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(775,625);
	glVertex2f(825,625);
	glVertex2f(825,675);
	glVertex2f(775,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(850,625);
	glVertex2f(900,625);
	glVertex2f(900,675);
	glVertex2f(850,675);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,0.74,1);
	glVertex2f(925,625);
	glVertex2f(975,625);
	glVertex2f(975,675);
	glVertex2f(925,675);
	glEnd();

	//green below airport extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(750,500);
	glVertex2f(1000,500);
	glVertex2f(1000,525);
	glVertex2f(750,525);
	glEnd();

	//airport teal extension
	glBegin(GL_POLYGON);
	glColor3f(0.56,0.73,0.56);
	glVertex2f(750,615);
	glVertex2f(1000,615);
	glVertex2f(1000,525);
	glVertex2f(750,525);
	glEnd();

	//lawn left extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(400,525);
	glVertex2f(400,575);
	glVertex2f(100,575);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glEnd();
	//left lawn
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(400,500);
	glVertex2f(0,500);
	glVertex2f(0,550);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glVertex2f(400,525);
	glEnd();

  glPushMatrix();
  glTranslatef(-500,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glScalef(0.8,0.8,1);
  glTranslatef(-200,100,0);
  drawTree();
  glPopMatrix();

	glFlush();
}

//function to draw broken scence
void drawBrokenPart(){

  //below the runway
	glColor3f(0.62,0.62,0.62);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(500,0);
	glVertex2f(500,150);
	glVertex2f(0,150);
	glEnd();

	//runway
	glColor3f(0.12941176, 0.12941176, 0.12941176);
	glBegin(GL_POLYGON);
	glVertex2f(0,150);
	glVertex2f(500,150);
	glVertex2f(500,400);
	glVertex2f(0,400);glColor3f(0.55, 0.27, 0.07);
	glEnd();

	//runway middle stripes
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	glVertex2f(0,250);
	glVertex2f(100,250);
	glVertex2f(100,300);
	glVertex2f(0,300);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(125,250);
	glVertex2f(225,250);
	glVertex2f(225,300);
	glVertex2f(125,300);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(250,250);
	glVertex2f(350,250);
	glVertex2f(350,300);
	glVertex2f(250,300);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(375,250);
	glVertex2f(475,250);
	glVertex2f(475,300);
	glVertex2f(375,300);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0,150);
	glVertex2f(225,150);
	glVertex2f(225,175);
	glVertex2f(0,175);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(250,150);
	glVertex2f(475,150);
	glVertex2f(475,175);
	glVertex2f(250,175);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0,400);
	glVertex2f(225,400);
	glVertex2f(225,375);
	glVertex2f(0,375);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(250,400);
	glVertex2f(475,400);
	glVertex2f(475,375);
	glVertex2f(250,375);
	glEnd();

	//runway final stripe
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	glVertex2f(475,150);
	glVertex2f(500,150);
	glVertex2f(500,450);
	glVertex2f(475,450);
	glEnd();

	//above the runway
	glBegin(GL_POLYGON);
	glColor3f(0.62,0.62,0.62);
	glVertex2f(0,400);
	glVertex2f(500,400);
	glVertex2f(500,450);
	glVertex2f(0,450);
	glEnd();

	//lawns above the road
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(500,450);
	glVertex2f(500,500);
	glVertex2f(0,500);
	glVertex2f(0,450);
	glEnd();

	//gundi outline
	//glLineWidth(20.0);
	glBegin(GL_LINES);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(500,500);
	glVertex2f(525,400);
	glVertex2f(525,400);
	glVertex2f(525,350);
	glVertex2f(525,350);
	glVertex2f(550,300);
	glVertex2f(550,300);
	glVertex2f(550,250);
	glVertex2f(550,250);
	glVertex2f(575,200);
	glVertex2f(575,200);
	glVertex2f(600,150);
	glVertex2f(600,150);
	glVertex2f(600,100);
	glVertex2f(600,100);
	glVertex2f(625,50);
	glVertex2f(625,50);
	glVertex2f(650,0);
	glEnd();

	//before gundi grass
	glColor3f(0.6, 0.8, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(500,500);
	glVertex2f(525,400);
	glVertex2f(500,400);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(525,400);
	glVertex2f(525,350);
	glVertex2f(500,350);
	glVertex2f(500,400);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(525,350);
	glVertex2f(550,300);
	glVertex2f(550,250);
	glVertex2f(575,200);
	glVertex2f(600,150);
	glVertex2f(600,100);
	glVertex2f(625,50);
	glVertex2f(650,0);
	glVertex2f(500,0);
	glVertex2f(500,400);
	glEnd();

	//gundi outline
	glLineWidth(20.0);
	glColor3f(0.55, 0.27, 0.07);
	glBegin(GL_LINES);
	glColor3f(0.55, 0.27, 0.07);
	glVertex2f(500,500);
	glVertex2f(525,400);
	glVertex2f(525,400);
	glVertex2f(525,350);
	glVertex2f(525,350);
	glVertex2f(550,300);
	glVertex2f(550,300);
	glVertex2f(550,250);
	glVertex2f(550,250);
	glVertex2f(575,200);
	glVertex2f(575,200);
	glVertex2f(600,150);
	glVertex2f(600,150);
	glVertex2f(600,100);
	glVertex2f(600,100);
	glVertex2f(625,50);
	glVertex2f(625,50);
	glVertex2f(650,0);
	glEnd();

	//ending gundi grass
	glColor3f(0.6, 0.8, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(1000,500);
	glVertex2f(975,450);
	glVertex2f(975,400);
	glVertex2f(950,350);
	glVertex2f(950,300);
	glVertex2f(925,250);
	glVertex2f(925,200);
	glVertex2f(900,150);
	glVertex2f(900,100);
	glVertex2f(875,50);
	glVertex2f(850,0);
	glVertex2f(1000,0);
	glEnd();



	//gundi finishing outline
	glLineWidth(20.0);
	glColor3f(0.55, 0.27, 0.07);
	glBegin(GL_LINES);
	glVertex2f(850,0);
	glVertex2f(875,50);
	glVertex2f(875,50);
	glVertex2f(900,100);
	glVertex2f(900,100);
	glVertex2f(900,150);
	glVertex2f(900,150);
	glVertex2f(925,200);
	glVertex2f(925,200);
	glVertex2f(925,250);
	glVertex2f(925,250);
	glVertex2f(950,300);
	glVertex2f(950,300);
	glVertex2f(950,350);
	glVertex2f(950,350);
	glVertex2f(975,400);
	glVertex2f(975,400);
	glVertex2f(975,450);
	glVertex2f(975,450);
	glVertex2f(1000,500);
	glEnd();

}

//Aeroplane front
void drawAeroplaneFrontPart() {

  //aeroplane front-cone
  glColor3f(0.95,0.95,0.95);
  glBegin(GL_POLYGON);
  glVertex2f(825,700);
  glVertex2f(850,700);
  glVertex2f(940,665);
  glVertex2f(975,600);
  glVertex2f(940,575);
  glVertex2f(860,550);
  glVertex2f(825,550);
  glEnd();

  //glColor3f(1,1,0);
  glPushMatrix();
  glScalef(50,40,0);
  glTranslatef(18.6,15.4,0);
  glutSolidSphere(1,100,100);
  glPopMatrix();

  glPushMatrix();
  glScalef(50,40,0);
  glTranslatef(18.4,15.7,0);
  glutSolidSphere(1,100,100);
  glPopMatrix();


  //airoplane middle
  glColor3f(0.95,0.95,0.95);
  glBegin(GL_POLYGON);
  glVertex2f(825,550);
  glVertex2f(450,550);
  glVertex2f(450,675);
  //glVertex2f(450,700);
  glVertex2f(825,700);
  glEnd();

  glColor3f(0.43921569, 0.43921569, 0.43921569);
  glBegin(GL_POLYGON);
  glVertex2f(910,600);
  glVertex2f(895,645);
  glVertex2f(840,665);
  glVertex2f(840,600);
  glEnd();

  //Aeroplane Windows
  glPushMatrix();
  glTranslatef(200,0,0);
  glColor3f(0.35686275, 0.35686275, 0.35686275);
    int tl=250,tu=300;
    for(i=0;i<5;i++){
      glBegin(GL_POLYGON);
        glVertex2f(tl+=40,600);
        glVertex2f(tl,650);
        glVertex2f(tu+=40,650);
        glVertex2f(tu,600);
      glEnd();
      tl+=20;
      tu+=20;
  }
  glPopMatrix();

  //aeroplane wings
  glColor3f(0.91, 0.9, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(450,580);
  glVertex2f(570,580);
  glVertex2f(400,425);
  glVertex2f(320,415);
  glEnd();
  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(350,420);
  glVertex2f(450,525);
  glVertex2f(415,540);
  glVertex2f(320,416);
  glEnd();

  glFlush();
}

//Aeroplane back
void drawAeroplaneBackPart(){
  //darksky();

  //airoplane middle
  glColor3f(0.95,0.95,0.95);
  glBegin(GL_POLYGON);
  glVertex2f(525,550);
  glVertex2f(250,550);
  glVertex2f(225,675);
  glVertex2f(450,700);
  glVertex2f(525,700);
  glEnd();

  //aeroplane end
  glColor3f(0.98,0.98,0.98);
  glBegin(GL_POLYGON);
  glVertex2f(250,550);
  glVertex2f(105,615);
  glVertex2f(35,880);
  glVertex2f(95,865);
  glVertex2f(225,675);
  glEnd();

  //aeroplane end wing
  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(35,880);
  glVertex2f(75,870);
  glVertex2f(135,690);
  glVertex2f(105,615);
  glEnd();

  //Aeroplane Windows
  glColor3f(0.35686275, 0.35686275, 0.35686275);
    int tl=250,tu=300;
    for(i=0;i<4;i++){
      glBegin(GL_POLYGON);
        glVertex2f(tl+=40,600);
        glVertex2f(tl,650);
        glVertex2f(tu+=40,650);
        glVertex2f(tu,600);
      glEnd();
      tl+=20;
      tu+=20;
  }

  //aeroplane wings
  glColor3f(0.91, 0.9, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(500,700);
  glVertex2f(370,885);
  glVertex2f(360,870);
  glVertex2f(415,695);
  glEnd();


  glColor3f(0.91, 0.09, 0.09);
  glBegin(GL_POLYGON);
  glVertex2f(370,885);
  glVertex2f(365,880);
  glVertex2f(460,700);
  glVertex2f(500,700);
  glEnd();


  glFlush();
}

void drawTrees(){
  glPushMatrix();
  glTranslatef(-500,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-300,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-250,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-50,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(70,-500,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(350,-500,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(400,-200,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(500,-500,0);
  drawTree();
  glPopMatrix();

}

void showBlasts(){
  glPushMatrix();
  glTranslatef(300,0,0);
  glScalef(0.8,0.8,1);
  blast();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(100,0,0);
  glScalef(0.8,0.8,1);
  blast();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(200,100,0);
  glScalef(0.8,0.8,1);
  blast();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(200,300,0);
  glScalef(0.8,0.8,1);
  blast();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(400,200,0);
  glScalef(0.8,0.8,1);
  blast();
  glPopMatrix();
}

//intro texts are here
void scene1(){
  sky();
  glPushMatrix();
  glTranslatef(-50,150,0);
  intro();
  glPopMatrix();

  glFlush();
}

//scene1 aeroplane takeoff-dubai
void scene2() {
  darksky();
  glPushMatrix();
  glTranslatef(0,400,0);
  star();
  glPopMatrix();
  drawDubaliAirPort();
  drawRunWay();
  //glLoadIdentity();
  glPushMatrix();

  glScalef(0.7,0.7,1);

  glTranslatef(startx,starty,1);
  //  flight moves forawrd
  startx+=speed;
  //lift off
  if(startx>300&&flag==0){

    flag=1;
    speed=3;
  }

  if(flag==0){
    drawLandingGear();
  }else{
    glPushMatrix();
    glTranslatef(0,tx,0);
    tx+=0.7;
    drawLandingGear();
    glPopMatrix();
    //glRotatef(30,0,0,1);

  }
  //take off the flight
  if(startx>200&&starty<500){
    starty+=speed;
  }

  drawAeroplane();
  glPopMatrix();

  if(startx>800){
    state=2;
    startx=0;
    starty=0;
    tx=0;
  }

  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,80);
  glVertex2f(1000,80);
  glVertex2f(1000,0);
  glEnd();

  //Add story part-1 here

  glFlush();

}

//scene2 aeroplane and clouds
void scene3(){
  glColor3fv(color[colorindex]);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(1000,0);
	glVertex2f(1000,1000);
	glVertex2f(0,1000);
  glEnd();

  glPushMatrix();
  glTranslatef(cx--,0,0);
  glPushMatrix();
  glTranslatef(300,100,0);
  drawClouds();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(700,-100,0);
  drawClouds();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-100,-100,0);
  drawClouds();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(100,-300,0);
  drawClouds();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(700,100,0);
  drawClouds();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(00,100,0);
  drawClouds();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(20,1,1);
  glScalef(10,20,1);
  glPopMatrix();


  glPushMatrix();
  glScalef(0.8,0.8,1);
  glTranslatef(startx,starty,1);
  startx+=speed;
  drawAeroplane();
  glPopMatrix();


  glPopMatrix();

  colorindex=(int)startx/100;
  if(startx>800){
    state=3;
    startx=-800;
    starty=500;
    flag=0;
    tx=100;
  }

  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,80);
  glVertex2f(1000,80);
  glVertex2f(1000,0);
  glEnd();

  //Add story part-2 here

  glFlush();



}

//scene-3 landing in glutInitDisplayMode
void scene4(){
  sky();
  drawIndianAirport();
  drawRunWay();
  int xspeed=3;
  glPushMatrix();
  glScalef(0.7,0.7,1);
  glTranslatef(startx,starty,1);


  if(startx>-300&&startx<6){
    glPushMatrix();
    glTranslatef(0,tx,0);
    tx-=0.7;
    drawLandingGear();
    glPopMatrix();
  }else if(flag==1){
    drawLandingGear();
  }

  if(startx<-200){
    startx+=xspeed;
  }
  else if(startx>-500&&startx<300){
    startx+=xspeed;
    starty-=3;
    flag=1;
  }else{
      startx+=xspeed;
  }

  drawAeroplane();

  glPopMatrix();



  if(startx>800){
    state=4;
    startx=-300;
  }
  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,80);
  glVertex2f(1000,80);
  glVertex2f(1000,0);
  glEnd();

  //Add story part-3 here

  glFlush();
}

//scene4 move forward in runway
void scene5(){
  sky();
  drawRunWay();

  glPushMatrix();
  glScalef(3,2,1);
  glTranslatef(0,-300,1);
  //lawn left extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(400,525);
	glVertex2f(400,575);
	glVertex2f(100,575);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glEnd();
	//left lawn
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(400,500);
	glVertex2f(0,500);
	glVertex2f(0,550);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glVertex2f(400,525);
	glEnd();

  glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(250,500);
	glVertex2f(0,500);
	glVertex2f(0,525);
	glVertex2f(250,525);
	glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(400,0,0);
  drawTree();
  glPopMatrix();

  glPushMatrix();
  glScalef(0.8,0.8,1);
  glTranslatef(350,100,0);
  drawTree();
  glPopMatrix();


  glPushMatrix();
  glScalef(10,2,1);
  glTranslatef(-200,-500,1);
  //lawn left extension
	glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(400,525);
	glVertex2f(400,575);
	glVertex2f(100,575);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glEnd();
	//left lawn
	glBegin(GL_POLYGON);
	glColor3f(0.5,1,0.0);
	glVertex2f(400,500);
	glVertex2f(0,500);
	glVertex2f(0,550);
	glVertex2f(75,550);
	glVertex2f(75,535);
	glVertex2f(100,525);
	glVertex2f(400,525);
	glEnd();

  glBegin(GL_POLYGON);
	glColor3f(0.19,0.80,0.19);
	glVertex2f(250,500);
	glVertex2f(0,500);
	glVertex2f(0,525);
	glVertex2f(250,525);
	glEnd();
  glPopMatrix();


  glPopMatrix();

  //drawRunWay();
  speed=3;
  glLoadIdentity();
  glPushMatrix();
  glScalef(0.7,0.7,1);
  glTranslatef(startx,-150,1);
  drawLandingGear();
  drawAeroplane();
  glPopMatrix();
  startx+=speed;

  glColor3f(1.0, 0.33, 0.0);
  drawfcircle(400,800,50);

  if(startx>900){
    state=5;
  }
  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,80);
  glVertex2f(1000,80);
  glVertex2f(1000,0);
  glEnd();

  //Add story part-4 here

  glFlush();

}

//scene-5  aerpolane crash
void scene6(){

  sky();
  drawTrees();
  drawBrokenPart();

  glPushMatrix();
  glScalef(0.7,0.7,0);
  glTranslatef(dpx,dpy,0);

  if(dpx>-50){

    glPushMatrix();
    glTranslatef(-200,0,0);
    glScalef(2,2,0);
    showBlasts();
    glPopMatrix();

    isCrashed=1;
    glFlush();

  }else{

    dpx+=2;
    drawLandingGear();
    drawAeroplane();

  }

  glPopMatrix();

  if(isCrashed==1){

    glPushMatrix();
    glScalef(0.7,0.7,1);
    glRotatef(-60,0,0,1);
    glTranslatef(-40,300,0);
    drawAeroplaneBackPart();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7,0.7,1);
    glRotatef(53,0,0,1);
    glTranslatef(250,-1500,0);
    drawAeroplaneFrontPart();
    glPopMatrix();

    showBlasts();
    drawTrees();

  }

  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,80);
  glVertex2f(1000,80);
  glVertex2f(1000,0);
  glEnd();

  //Add story part-5 here

  glFlush();
}

//scene-6 story about the crash
void end(){
  glColor3f(0.2,0.1,0.5);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,1000);
  glVertex2f(1000,1000);
  glVertex2f(1000,0);
  glEnd();

  //Add story conclusion here
  //end of the story
}

//GL display function
void display()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	if(state==0){
		scene1();
	}

	if(state==1){
		scene2();

	}

  if(state==2){
    scene3();
  }

  if (state==3) {
    scene4();
  }

  if(state==4){
    scene5();
  }
  if(state==5){
    scene6();
  }

  if(state==6){
    end();
  }

  glutSwapBuffers();
  glutPostRedisplay();
}

//main fucntion
int main(int argc,char **argv)
 {
  glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("aeroplane Crash");
	glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
	glutMainLoop();
}
