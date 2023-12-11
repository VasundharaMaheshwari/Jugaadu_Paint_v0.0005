#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
int i,j,x1,y1,x2,y2,side,xc,yc,oldpt[8],points[8];
int undo,redo;
float xnew1,ynew1;
void shapedrawing(int color,int pt[8]){
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    cleardevice();
    drawpoly(4,pt);
    fillpoly(4,pt);
}
void updatepoints(int pt[8],int point[8]){
	int i;
	for(i=0;i<8;i++){
		pt[i]=point[i];
	}
}
void undoaction(int color,int undo,int points[8]){
	switch(undo)
	{
		case 1: cleardevice();
			shapedrawing(color,oldpt);
			break;
		case 2: updatepoints(oldpt,points);
			break;
		default: gotoxy(1,21);
			 printf("Wrong Choice. Restart the Program.");
			 getch();
			 exit(0);
	}
}
void redoaction(int color,int redo,int points[8]){
	switch(redo){
		case 1: cleardevice();
			shapedrawing(color,points);
			updatepoints(oldpt,points);
			break;
		case 2: break;
		default: gotoxy(1,21);
			 printf("Wrong Choice. Restart the program.");
			 getch();
			 exit(0);
	}
}
int translate(int coor,int coorchange){
       int coornew=coor+coorchange;
       return coornew;
}
int scale(int coor,int coorchange){
      int coornew;
      if(coorchange>0){
	coornew=coor*coorchange;}
      if(coorchange<0){
	coornew=(int)coor/abs(coorchange);
      }
      if(coorchange==0){
	coornew=coor;
      }
      return coornew;
}
int shearx(int x,int y,int xc){
	long xnew=x+(y*xc);
	return((int)xnew);
}
int sheary(int x,int y,int yc){
	long ynew=y+(x*yc);
	return((int)ynew);
}
void main(){
	int gd=DETECT,gm,effchoice,choice,shapechoice,color,shearchoice,bgchoice,bgcolor,radiu;
	float a,maxxx,maxyy;
	int x4,y4,ccolor,cchoice,fc,fontn,ts,tcolor,tchoice;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	printf("Welcome to Jugaadu Paint\nPress any key to continue....");
	getch();
	cleardevice();
	gotoxy(1,1);
	printf("Choose which shape to draw-\n1.Square\n2.Rectangle\nNOTE:Remember that the drawn shape will be filled\nEnter your choice - ");
	scanf("%d",&shapechoice);
	cleardevice();
	switch(shapechoice){
	       case 1: gotoxy(1,1);
		       printf("Enter the starting coordinate and the side length of the square - ");
		       scanf("%d %d %d",&x1,&y1,&side);
		       x2=x1+side;
		       y2=y1+side;
		       break;
	       case 2: gotoxy(1,1);
		       printf("Enter the coordinates of the rectangle - ");
		       scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		       break;
	       default: gotoxy(1,1);
			printf("Wrong Input\nPlease restart program");
			getch();
			exit(0);
	}
	cleardevice();
	gotoxy(1,1);
	printf("Colour Menu\n1.Red\n2.Blue\n3.Green\nEnter your choice - ");
	scanf("%d",&choice);
	cleardevice();
	switch(choice){
		case 1: color=4;
			break;
		case 2: color=1;
			break;
		case 3: color=2;
			break;
		default: printf("Wrong Input\nPlease restart program");
			 getch();
			 exit(0);
	}
	cleardevice();
	oldpt[0]=x1;
	oldpt[1]=y1;
	oldpt[2]=oldpt[0];
	oldpt[3]=y2;
	oldpt[4]=x2;
	oldpt[5]=oldpt[3];
	oldpt[6]=oldpt[4];
	oldpt[7]=oldpt[1];
	shapedrawing(color,oldpt);
	delay(2000);
	cleardevice();
	gotoxy(1,1);
	printf("List of effects -\n1.Translate\n2.Scale\n3.Rotate\n4.Shear\nEnter your choice - ");
	scanf("%d",&effchoice);
	switch(effchoice){
		case 1: printf("Enter Translation Factors - ");
			scanf("%d %d",&xc,&yc);
			cleardevice();
			points[0]=translate(x1,xc);
			points[1]=translate(y1,yc);
			points[2]=points[0];
			points[3]=translate(y2,yc);
			points[4]=translate(x2,xc);
			points[5]=points[3];
			points[6]=points[4];
			points[7]=points[1];
			break;
		case 2: printf("Enter scaling factors - ");
			scanf("%d %d",&xc,&yc);
			cleardevice();
			points[0]=scale(x1,xc);
			points[1]=scale(y1,yc);
			points[2]=points[0];
			points[3]=scale(y2,yc);
			points[4]=scale(x2,xc);
			points[5]=points[3];
			points[6]=points[4];
			points[7]=points[1];
			break;
		case 3: printf("Enter angle of rotation - ");
			scanf("%f",&a);
			cleardevice();
			a=(a*3.14)/180;
			points[0]=(int)((x1*cos(a))-(y1*sin(a)));
			points[1]=(int)((x1*sin(a))+(y1*cos(a)));
			points[2]=(int)((x1*cos(a))-(y2*sin(a)));
			points[3]=(int)((x1*sin(a))+(y2*cos(a)));
			points[4]=(int)((x2*cos(a))-(y2*sin(a)));
			points[5]=(int)((x2*sin(a))+(y2*cos(a)));
			points[6]=(int)((x2*cos(a))-(y1*sin(a)));
			points[7]=(int)((x2*sin(a))+(y1*cos(a)));
			break;
		case 4: printf("1.ShearX\n2.ShearY\nEnter your choice - ");
			scanf("%d",&shearchoice);
			switch(shearchoice){
				case 1: printf("Enter ShearX Factor - ");
					scanf("%d",&xc);
					points[0]=shearx(x1,y1,xc);
					points[1]=y1;
					points[2]=shearx(x1,y2,xc);
					points[3]=y2;
					points[4]=shearx(x2,y2,xc);
					points[5]=y2;
					points[6]=shearx(x2,y1,xc);
					points[7]=y1;
					cleardevice();
					break;
				case 2: printf("Enter ShearY Factor - ");
					scanf("%d",&yc);
					points[0]=x1;
					points[1]=sheary(x1,y1,yc);
					points[2]=x1;
					points[3]=sheary(x1,y2,yc);
					points[4]=x2;
					points[5]=sheary(x2,y2,yc);
					points[6]=x2;
					points[7]=sheary(x2,y1,yc);
					cleardevice();
					break;
				default: printf("Wrong Choice. Restart Program");
					 getch();
					 exit(0);
			}
			break;
		default: printf("Wrong Input. Restart the program");
			 getch();
			 exit(0);
	}
	shapedrawing(color,points);
	delay(2000);
	cleardevice();
	gotoxy(1,1);
	printf("Would you like to undo your last action? (1-Yes/2-No) - ");
	scanf("%d",&undo);
	undoaction(color,undo,points);
	if(undo==1){
		delay(2000);
		gotoxy(1,1);
		cleardevice();
		printf("Would you like to undo your last action? (1-Yes/2-No) - ");
		scanf("%d",&redo);
		redoaction(color,redo,points);
	}
	delay(2000);
	cleardevice();
	gotoxy(1,1);
	printf("Background Colour Options - \n1.Yellow\n2.Cyan\n3.Light Gray\nEnter your background color choice - ");
	scanf("%d",&bgchoice);
	switch(bgchoice){
		case 1: bgcolor=14;
			break;
		case 2: bgcolor=3;
			break;
		case 3: bgcolor=7;
			break;
		default: printf("No such choice. Keeping background color as BLACK.");
			 bgcolor=0;
	}
	gotoxy(1,1);
	cleardevice();
	printf("Lets add a circle to wrap things up...\nEnter centre point - ");
	scanf("%d %d",&x4,&y4);
	printf("Enter radius - ");
	scanf("%d",&radiu);
	printf("Color Menu - \n1.White\n2.Light Blue\n3.Magenta\nEnter your choice of color - ");
	scanf("%d",&cchoice);
	switch(cchoice){
		case 1: ccolor=15;
			break;
		case 2: ccolor=9;
			break;
		case 3: ccolor=5;
			break;
		default: printf("Wrong Input. Restart the program.");
			 getch();
			 exit(0);
	}
	cleardevice();
	setbkcolor(bgcolor);
	shapedrawing(color,oldpt);
	setcolor(ccolor);
	circle(x4,y4,radiu);
	setfillstyle(SOLID_FILL,ccolor);
	floodfill(x4,y4,ccolor);
	delay(2000);
	cleardevice();
	setbkcolor(BLACK);
	gotoxy(1,1);
	printf("Time to give a caption\nFont List - \n1.Simplex Font\n2.Sans Serif Font\n3.Gothic Font\nEnter your choice - ");
	scanf("%d",&fc);
	switch(fc){
		case 1: fontn=6;
			break;
		case 2: fontn=3;
			break;
		case 3: fontn=4;
			break;
		default: printf("Continuing with default font.");
			 fontn=0;
	}
	printf("Enter text size(1-10)- ");
	scanf("%d",&ts);
	if(ts>10){
		printf("Too big font. Program terminated.");
		getch();
		exit(0);
	}
	settextstyle(fontn,HORIZ_DIR,ts);
	printf("Font Colour - \n1.Dark Grey\n2.Light Green\n3.Light Magenta\nEnter your choice - ");
	scanf("%d",&tchoice);
	switch(tchoice){
		case 1: tcolor=8;
			break;
		case 2: tcolor=10;
			break;
		case 3: tcolor=13;
			break;
		default: printf("Wrong Input. Program Terminated.");
			 getch();
			 exit(0);
	}
	cleardevice();
	setbkcolor(bgcolor);
	shapedrawing(color,oldpt);
	setcolor(ccolor);
	setfillstyle(SOLID_FILL,ccolor);
	circle(x4,y4,radiu);
	floodfill(x4,y4,ccolor);
	setcolor(tcolor);
	outtextxy(5,5,"Your creation - ");
	outtextxy(5,350,"Thank you for using Jugaadu Paint!");
	getch();
	closegraph();
}