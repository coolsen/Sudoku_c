/*
 *************************************************** File for windows on windows branch ***************************************************************
 *				Windows does not support color on terminal so it's off
 *
 *				Windows does not support timers with any precition so it's off
 *
 *				Windows version with CR-LF line-ending
 */



#define Sz 9			//SudSize
#define SqSz ((Sz)*(Sz))	//SudSize
#define KSz 3			//Kvadrat Size 3(*3)
#define mskAll  ((1 << (Sz+1))-2)

#define TTYColor 0	//if your TTY does not support colors turn it of

unsigned char TTyBlueBuf[] = "\x1b[34m";
unsigned char TTyYellBuf[] = "\x1b[33m";
unsigned char TTyWhiteBuf[] = "\x1b[39m";



#include <stdio.h>
#include <stdint.h>
#include <time.h>
unsigned char possi[26];
unsigned char mat[SqSz],matB[SqSz],matSt[SqSz],matStB[SqSz], inBuf[1000];
unsigned short int c,r,i, rmsk[Sz], cmsk[Sz], kmsk[Sz], msk;
unsigned int todo=0,oldTodo=0,try=0,tryall=0,inLng,cnt[Sz+1];
int sud_cnt;
unsigned char rN[] = { 0,0,0,0,0,0,0,0,0,
                       1,1,1,1,1,1,1,1,1,
		       2,2,2,2,2,2,2,2,2,
		       3,3,3,3,3,3,3,3,3,
		       4,4,4,4,4,4,4,4,4,
                       5,5,5,5,5,5,5,5,5,
                       6,6,6,6,6,6,6,6,6,
                       7,7,7,7,7,7,7,7,7,
                       8,8,8,8,8,8,8,8,8};
unsigned char cN[] = { 0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8,
                       0,1,2,3,4,5,6,7,8};

unsigned char kN[] = { 0,0,0,1,1,1,2,2,2,
                       0,0,0,1,1,1,2,2,2,
                       0,0,0,1,1,1,2,2,2,
                       3,3,3,4,4,4,5,5,5,
                       3,3,3,4,4,4,5,5,5,
                       3,3,3,4,4,4,5,5,5,
                       6,6,6,7,7,7,8,8,8,
                       6,6,6,7,7,7,8,8,8,
                       6,6,6,7,7,7,8,8,8};


unsigned char fltR[9][9] = {{ 0, 1, 2, 3, 4, 5, 6, 7, 8},
                            { 9,10,11,12,13,14,15,16,17},
                            {18,19,20,21,22,23,24,25,26},
                            {27,28,29,30,31,32,33,34,35},
                            {36,37,38,39,40,41,42,43,44},
                            {45,46,47,48,49,50,51,52,53},
                            {54,55,56,57,58,59,60,61,62},
                            {63,64,65,66,67,68,69,70,71},
                            {72,73,74,75,76,77,78,79,80}};


unsigned char fltC[9][9] = {{ 0, 9,18,27,36,45,54,63,72},
                            { 1,10,19,28,37,46,55,64,73},
                            { 2,11,20,29,38,47,56,65,74},
                            { 3,12,21,30,39,48,57,66,75},
                            { 4,13,22,31,40,49,58,67,76},
                            { 5,14,23,32,41,50,59,68,77},
                            { 6,15,24,33,42,51,60,69,78},
                            { 7,16,25,34,43,52,61,70,79},
                            { 8,17,26,35,44,53,62,71,80}};

unsigned char fltK[9][9] = {{ 0, 1, 2, 9,10,11,18,19,20},
                            { 3, 4, 5,12,13,14,21,22,23},
                            { 6, 7, 8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};

void inJSONpre(int n) {
switch(n)
{
case 0:
  inLng = sprintf(inBuf, //Fill inBuf with JSON string
"[7,0,0,0,9,0,0,0,0,0,0,4,6,0,2,0,0,0,2,0,0,0,0,7,0,6,5,0,7,9,0,0,0,5,0,3,0,0,2,0,0,0,9,0,0,3,0,6,0,0,0,8,1,0,6,4,0,5,0,0,0,0,7,0,0,0,7,0,3,4,0,0,0,0,0,0,4,0,0,0,2]");
  break;
case 1:
  inLng = sprintf(inBuf,
"[0,3,0,7,0,0,2,9,0,2,5,8,0,0,1,7,0,0,0,0,0,0,0,5,0,0,0,0,0,9,0,0,0,8,0,0,0,0,0,4,2,3,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,8,0,0,0,0,0,0,0,5,6,0,0,9,3,7,0,9,6,0,0,4,0,8,0]");
  break;
case 2:
  inLng = sprintf(inBuf,
"[0,0,0,0,1,2,0,0,8,0,0,7,6,0,0,2,0,3,0,5,8,0,0,9,7,1,0,5,7,0,2,0,0,0,0,0,0,9,1,3,0,7,4,2,0,0,0,0,0,0,6,0,3,7,0,1,2,8,0,0,9,5,0,3,0,5,0,0,4,6,0,0,4,0,0,1,7,0,0,0,0]");
  break;
case 3:
  inLng = sprintf(inBuf,
"[0,2,0,0,8,0,9,4,0,0,0,0,0,0,2,3,0,0,5,0,4,0,0,0,0,0,1,4,0,0,0,0,8,0,0,3,0,0,0,0,9,0,0,0,0,6,0,0,1,0,0,0,0,7,8,0,0,0,0,0,2,0,9,0,0,1,6,0,0,0,0,0,0,4,3,0,5,0,0,7,0]");
  break;
case 4:
  inLng = sprintf(inBuf,
"[0,0,0,0,0,0,1,0,4,0,6,0,3,0,0,0,2,0,2,0,0,0,0,7,0,0,9,8,0,0,5,0,0,0,4,0,0,5,6,4,0,9,3,8,0,0,3,0,0,0,2,0,0,7,6,0,0,7,0,0,0,0,1,0,7,0,0,0,4,0,9,0,5,0,4,0,0,0,0,0,0]");
  break;
case 5:
  inLng = sprintf(inBuf,
"[0,0,3,0,4,0,0,9,0,0,5,4,0,0,0,3,0,0,7,6,0,0,0,0,1,0,0,0,0,0,0,0,9,0,3,8,0,0,0,0,2,0,0,0,0,6,3,0,7,0,0,0,0,0,0,0,6,0,0,0,0,5,3,0,0,2,0,0,0,7,1,0,0,8,0,0,1,0,9,0,0]");
  break;


} // switch
return;
} //inJSONpre()

void outMat() {
        unsigned char  *ptr,lineBuf[180];
        int i,PSzA=0, PSz, PrColor=TTYColor; // Printed Size Accumulator, Printed Size (from last call to sprintf()), PrColor to aviod compilation warning
        unsigned char *StTTYCol = TTyWhiteBuf;
        StTTYCol = TTyYellBuf;
        printf("\r\n");
        ptr= lineBuf;
        todo=0;
	for (i=0, r=0; r < Sz; r++) {
                if (r!= 0 && (r % KSz) == 0 ) printf("----------------------------\r\n");
                ptr= lineBuf;
        	for (c=0; c < Sz; c++) {
			PSz=0;
                        if (c!= 0 && (c % KSz) == 0 ) {
	                	PSz = sprintf (ptr, "|");
	                	ptr += PSz;
                        }
                        if (mat[i] == 0) {
				PSz = sprintf (ptr, "   ");
				i++;
			}
                	else {
				if (PrColor) {
					if (matSt[i] == 1) StTTYCol = TTyWhiteBuf;
					if (matSt[i] == 2) StTTYCol = TTyBlueBuf;
					if (matSt[i] == 3) StTTYCol = TTyYellBuf;
					PSz = sprintf (ptr, "%s %d %s",StTTYCol,mat[i++],TTyWhiteBuf);
				}
				else {
					PSz = sprintf (ptr, " %d ",mat[i++]);
				}
			}
                	ptr += PSz;
                } //for c
                printf ("%s\r\n",lineBuf);
        }  // for r-i

        todo=0;

        for (i = 1; i < Sz+1; i++) {
            todo+= Sz - cnt[i];
            if (Sz != cnt[i]) printf("%d:%d ",i,cnt[i]);

        }
        if (todo != 0)  printf ("todo: %d try: %d\r\n",todo,try);

}

int writeMat(int flt,int n, int st) {
unsigned short msk,nmsk;
unsigned int ridx,cidx,kidx;

//if (st == 3) printf("[%d]=%d ",flt,n);

if (mat[flt] != 0) return 4;
ridx = rN[flt]; // get index of row mask
cidx = cN[flt]; // get index of col mask
kidx = kN[flt]; // get index of kvad mask//printf("I writeMat() i=%d n=%d \r\n",i,n);
//if (st != 1) printf("writeMat(): ridx=%d cidx=%d kidx=%d  ",ridx,cidx,kidx);
msk = rmsk[ridx];
msk = msk & cmsk[cidx];
msk = msk & kmsk[kidx];
//if (st != 1) printf ("writeMat(flt=%d,n=%d,,,): msk= %d ",flt,n,msk);
//if (st != 1) printf ("%d->%d ",n,flt);
nmsk = 1 << n ;
msk = msk & nmsk;
//printf ("writeMat(flt=%d,n=%d,,,): msk= %d nmsk= %d",flt,n,msk);
if (msk == 0) return 5;
msk = mskAll - msk;
rmsk[ridx] = rmsk[ridx] & msk; // unmask
cmsk[cidx] = cmsk[cidx] & msk;
kmsk[kidx] = kmsk[kidx] & msk;


//printf (" w-msk= %d \r\n",msk);
if (mat[flt] == 0) {
  mat[flt] = n;
  matSt[flt] = st;
  cnt[n]++;
}
else return 3;
return 0;
}


int readJSON(unsigned char *buf) {
unsigned char *t;
int i=0,n,ch,st=1,Jst=0,ERROR=0; // n scannet number,C count
ch= *buf;
if (ch == 0)return 1;
for ( ;ch !=0;buf++, ch= *buf) {
    if (ch == ' ') continue;   //whitespace
    if (ch == '\t') continue;   //whitespace
    if (ch == '\r') continue;   //whitespace
    if (ch == '\n') continue;   //whitespace


    if ((ch == '[')  && Jst==0) {Jst=1;continue;}
    if ((ch == ']')  && Jst==1) {Jst=0;continue;}
    if (ch == ',' && Jst==1)    {i++; continue;}

    if ((ch >= '0' && (ch < ('9' +1))) && Jst==1) {
//        printf("før sscanf() ch=%c i=%d ERROR=%d\r\n",ch,i,ERROR);
	c = sscanf(buf,"%d",&n);
//        printf("før sscanf() n=%d i=%d ERROR=%d\r\n",n,i,ERROR);
        if (n > 0 && (n < (9 +1))) { ERROR = writeMat(i, n, st);if (ERROR != 0){printf("After writeMat ERROR=%d",ERROR);return ERROR;}}
    }
    else {ERROR = 2;printf("i else ch=%c i=%d ERROR=%d\r\n",ch,i,ERROR);break; }
} //for
//printf("Slut på readJSON() i=%d Jst=%d ERROR=%d\r\n",i,Jst,ERROR);


return ERROR;
} // readJSON()

int readPre(int n) {
inJSONpre(n);

if (readJSON(inBuf) != 0) return 1;
return 0;
}


int fltGetPz(unsigned char *poss, int flt) { // get possibilities for on field flt
int ret=0, i;
unsigned short msk;
unsigned int ridx,cidx,kidx;
try++;
//printf("mat[%d]= %d  ",flt,mat[flt]);

if (mat[flt] != 0) return 0;
ridx = rN[flt]; // get index of row mask
cidx = cN[flt]; // get index of col mask
kidx = kN[flt]; // get index of col mask
//printf("ridx=%d cidx=%d kidx=%d  ",ridx,cidx,kidx);
msk = rmsk[ridx];
msk = msk & cmsk[cidx];
msk = msk & kmsk[kidx];
//if (flt == 0) printf ("++hej msk= %03X \r\n",msk);

for ( i=1 ; i < Sz + 1; i++) {
    msk = msk >> 1;
    if ((msk & 1 ) == 1) {
        ret++;
        *poss = i;
        poss++;
    }
} //for
return ret;
} //func

int fltTryN(int n, int flt) { // can flt be n ? Answer 0=false 1=true
int ret=0, i;
unsigned short msk;
unsigned int ridx,cidx,kidx;
try++;
//printf("mat[%d]= %d  ",flt,mat[flt]);

if (mat[flt] != 0) return 0;
ridx = rN[flt]; // get index of row mask
cidx = cN[flt]; // get index of col mask
kidx = kN[flt]; // get index of col mask
//printf("ridx=%d cidx=%d kidx=%d  ",ridx,cidx,kidx);
msk = rmsk[ridx];
msk = msk & cmsk[cidx];
msk = msk & kmsk[kidx];
//printf ("msk= %d \r\n",msk);

msk = msk >> n;
if ((msk & 1 ) == 1) ret++;

return ret;
} //func


void init() {
	todo=0; try = 0;
        msk = mskAll;
	for (i=0; i < SqSz; i++) {
	  mat[i] = 0;
	  matSt[i] = 0;
	} //for

	for (i=0; i < Sz; i++) {
	  rmsk[i] = msk;
	  cmsk[i] = msk;
	  kmsk[i] = msk;
	} //for
        for (i = 0 ; i < Sz +1; i++) {
          cnt[i] =0;
        }

}

backup() {
int i;
//printf("Backup  ");
for (i=0; i < SqSz; i++) {
matB[i] = mat[i];
matStB[i] = matSt[i];
}
}
restore() {
int i,ERROR;
init();
for (i=0; i < SqSz; i++) {

    if (matB[i] != 0) { ERROR = writeMat(i, matB[i],matStB[i]);  }
    if (ERROR != 0) printf("ERROR  %d",ERROR);
//    mat[i] = matB[i];
//    matSt[i] = matStB[i];
}
//printf("\r\n");
}



SolveAllDom(int n) {
int i,c,ca,ci,x,y,ERROR;
//   ------------------------------------- row
    for (x=0 ; x < Sz; x++) { // next row
        c=0;
        ca=0;
//        printf("solve() digit: %d row: %d field: ",n,x);
        for (y=0 ; y < Sz; y++) { // next field in row
            i=fltR[x][y];
            if (mat[i] == 0 ) {

                c = fltTryN(n, i); // if n can go in mat[i] c will be add with 1
                if (c == 1) ci=i;
                ca += c;
//           printf(",i%d:c%d ",i,ca);
            } // if
        } // for y
//    printf("\r\n");
        if (ca ==  1)  {
//            printf("ROD-");
            ERROR = writeMat(ci, n, 2);
            if (ERROR) printf("ERROR %d\r\n",ERROR);
        }

    } // for x


//  ---------------------------------- column
    for (x=0 ; x < Sz; x++) { // next kvadrat
        c=0;
        ca=0;
//        printf("solve() digit: %d row: %d field: ",n,x);
        for (y=0 ; y < Sz; y++) { // next field in col
            i=fltC[x][y];
            if (mat[i] == 0 ) {

                c = fltTryN(n, i); // if n can go in mat[i] c will be add with 1
                if (c == 1) ci=i;
                ca += c;
//           printf(",i%d:c%d ",i,ca);
            } // if
        } // for y
//    printf("\r\n");
      if (ca ==  1)  {
//          printf("COD-");
          ERROR = writeMat(ci, n, 2);
          if (ERROR) printf("ERROR %d\r\n",ERROR);
      }

    } // for x


//  ---------------------------------- Kvad
    for (x=0 ; x < Sz; x++) { // next kvadrat
        c=0;
        ca=0;
//        printf("solve() digit: %d row: %d field: ",n,x);
        for (y=0 ; y < Sz; y++) { // next field in kvadrat
            i=fltK[x][y];
            if (mat[i] == 0 ) {

                c = fltTryN(n, i); // if n can go in mat[i] c will be add with 1
                if (c == 1) ci=i;
                ca += c;
            } // if
        } // for y
        if (ca ==  1)  {
//            printf("KOD-");
            ERROR = writeMat(ci, n, 2);
            if (ERROR) printf("ERROR %d\r\n",ERROR);
        }
    } // for x
}




findNsolveDom() {
int c,ci,ca,lcnt,x,y,n,i,ERROR;

for (i = 1; i < Sz; i++) {
    todo=0;
    if (cnt[i]==Sz) continue;
    todo+= Sz - cnt[i];
    if (cnt[i] > lcnt) {
      lcnt=cnt[i];
      n=i;

    } //if
} //for

    for (x=0 ; x < Sz; x++) { // next row
        c=0;
        ca=0;
//        printf("solve() digit: %d row: %d field: ",n,x);
        for (y=0 ; y < Sz; y++) { // next field in row
            i=fltR[x][y];
            if (mat[i] == 0 ) {

                c = fltTryN(n, i); // if n can go in mat[i] c will be add with 1
                if (c == 1) ci=i;
                ca += c;
//           printf(",i%d:c%d ",i,ca);
            } // if
        } // for y
//    printf("\r\n");
        if (ca ==  1)  {
//            printf("NOD-");
            ERROR = writeMat(ci, n, 2);
            if (ERROR) printf("ERROR %d\r\n",ERROR);
        }

    } // for x




}
solveOnePoss() {
int c,i,ERROR;
unsigned char *p=possi;
for (i = 0; i < SqSz; i++) {
    if (mat[i]==0) {
      p=possi;
      c=fltGetPz(possi, i);
      if (c == 1) {
//        printf("Ons-",i,*p);
        ERROR = writeMat(i, *p, 2);
        if (ERROR != 0) printf("Solve(): O-s ERROR =%d\r\n",ERROR);
      }
    }
}
}
void solve() {
unsigned char row,col,kvd,c,ca,n,lcnt=0,ret=0;
unsigned char *p=possi;
int ERROR=0,gSt=0,s,st=2,flt,x,y,i,ii,pp,ci,bi,r;
status();      // reset

for (i=0; ((i<10) && (todo !=0)) ; i++ ) { // i<10 now
    solveOnePoss();
    findNsolveDom();
    solveOnePoss();

    s=status();
    if  (s == 2) break; //todo = 0 break on for i

//    findNsolveDom();
//    solveOnePoss();
    for (n=0 ; n < Sz+1; n++) { // next digit

        if (cnt[n] == Sz) continue;

        SolveAllDom(n);
    } //for n
    s=status();
    if  (s == 2) break; //todo = 0 break on for i
    if  (s == 0) {
        	p=possi;
        	c=fltGetPz(possi, ii);
        	if (c == 2) {
//			printf("C==2 *p++=%d",*p);
			p++;
//			printf("ii=%d  *p--=%d __________________",ii,*p);
                        ERROR = writeMat(ii, 7, 3);
			continue;
		}


if (sud_cnt == 1) { ERROR = writeMat(ii, 6, 3); }
if (sud_cnt == 4  & ii == 0) {  ERROR = writeMat(ii, 7, 3); }
if (sud_cnt == 5  & ii == 0) { ERROR = writeMat(ii, 8, 3); ERROR = writeMat(1, 1, 3); }
else {
//        printf("eGuess ii=%d -> %d \r\n",ii,1);
        ERROR = writeMat(ii, 1, 3);
		}

    }//if

}  // for i
} //solve




int status() { //returns: 0 if no progress, and 1 if some progress, 2 if todo=0
int i,ret=0;
        todo = 0;
        for (i = 1; i < Sz+1; i++) {
            todo+= Sz - cnt[i];
        }
        if (todo < oldTodo) ret=1;
        oldTodo = todo;
        if (todo == 0) ret=2;
        return ret;
}




int main (int argc,int *argv[]) {
int flt,cnt;
unsigned char *p=possi;
//struct timespec start, end;
for (cnt=0; cnt<100000/6;cnt++) {
	for (sud_cnt=0; sud_cnt<6 ;sud_cnt++) {
		init();
		readPre(sud_cnt);

		solve();
		tryall += try;
                if (cnt == 100) {
				outMat();
				printf ("todo: %d try: %d tryall: %d sud_cnt: %d \r\n",todo,try,tryall,sud_cnt);
				}

	} //for i
} //for cnt
return 0;
}
