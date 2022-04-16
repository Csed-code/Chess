#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

char fakeboard[8][8]={
                    {'R','N','B','Q','K','B','N','R'},
                    {'P','P','P','P','P','P','P','P'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'p','p','p','p','p','p','p','p'},
                    {'r','n','b','q','k','b','n','r'},
                    };

int counter1 = 0, counter2 = 0;
int i ,j ,temp ,count = 0 ,yosef = 0,yosef2=0;
int player1options(char board[8][8], char col[8][8], char displayed_white[16], char displayed_black[16]);
int player2options(char board[8][8], char col[8][8], char displayed_white[16], char displayed_black[16]);
int PLAYER_INDICATOR=0;

int pos_white_king[1][2]={{7,4}}; int wtemp_pos[2];
int pos_black_king[1][2]={{0,4}}; ; int btemp_pos[2];
int pos_w[1][2]={{}},pos_b[1][2];
int n=0,n_b=0;

// Undo and Redo.

char ch_w[999],ch_b[999];
void saveWhitemove(char board[8][8], char displayed_white[16], char displayed_black[16],int indicator){
    FILE *f_w;
    itoa(counter1,ch_w,10);
    f_w = fopen(ch_w,"w");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
           fputc(board[i][j],f_w);
        }
    }
    for(i=0;i<16;i++){
        fputc(displayed_white[i],f_w);
        fputc(displayed_black[i],f_w);

    }
    fputc(indicator,f_w);
    for(i=0;i<2;i++){
        fputc(pos_white_king[0][i],f_w);
        fputc(pos_black_king[0][i],f_w);
    }

    fclose(f_w);
    return 0;
}
void loadWhitemove(char board[8][8], char displayed_white[16], char displayed_black[16]){
    FILE *f_w;
    itoa(counter1,ch_w,10);
    f_w = fopen(ch_w,"r");


    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            board[i][j] = fgetc(f_w);

        }
    }
     for(i=0;i<16;i++){
        displayed_white[i]=fgetc(f_w);
        displayed_black[i]=fgetc(f_w);

    }
    PLAYER_INDICATOR = fgetc(f_w);
    for(i=0;i<2;i++){
        pos_white_king[0][i]=fgetc(f_w);
        pos_black_king[0][i]=fgetc(f_w);
    }

    fclose(f_w);
    return 0;
}
void saveBlackmove(char board[8][8], char displayed_white[16], char displayed_black[16],int indicator){
    FILE *f_b;
    itoa(counter2+301,ch_b,10);
    f_b = fopen(ch_b,"w");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
           fputc(board[i][j],f_b);
        }
    }
    for(i=0;i<16;i++){
        fputc(displayed_white[i],f_b);
        fputc(displayed_black[i],f_b);

    }
    fputc(indicator,f_b);
    for(i=0;i<2;i++){
        fputc(pos_white_king[0][i],f_b);
        fputc(pos_black_king[0][i],f_b);
    }

    fclose(f_b);
    return 0;
}
void loadBlackmove(char board[8][8], char displayed_white[16], char displayed_black[16]){
    FILE *f_b;
    itoa(counter2+301,ch_b,10);
    f_b = fopen(ch_b,"r");


    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            board[i][j] = fgetc(f_b);

        }
    }
     for(i=0;i<16;i++){
        displayed_white[i]=fgetc(f_b);
        displayed_black[i]=fgetc(f_b);

    }
    PLAYER_INDICATOR = fgetc(f_b);
    for(i=0;i<2;i++){
        pos_white_king[0][i]=fgetc(f_b);
        pos_black_king[0][i]=fgetc(f_b);
    }

    fclose(f_b);
    return 0;
}

// Files Modifier.

void save(char board[8][8], char displayed_white[16], char displayed_black[16]){
    int i,j;

    FILE *fp1;


    fp1 = fopen("Chess.txt","w");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
           fputc(board[i][j],fp1);
        }
    }
    for(i=0;i<16;i++){
        fputc(displayed_white[i],fp1);
        fputc(displayed_black[i],fp1);
    }
    PLAYER_INDICATOR+='0';

    fputc(PLAYER_INDICATOR,fp1);

    fclose(fp1);

}
void load(char board[8][8], char displayed_white[16], char displayed_black[16]){
    int i,j;

    FILE *fp1;

    fp1 = fopen("Chess.txt","r");

    if(!(fp1==NULL)){
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            board[i][j] = fgetc(fp1);

        }
    }
     for(i=0;i<16;i++){
        displayed_white[i]=fgetc(fp1);
        displayed_black[i]=fgetc(fp1);
    }
    PLAYER_INDICATOR = fgetc(fp1);

    }
    else{
            printf("Error\n");
            exit(0);

    }

    fclose(fp1);


}

// Scanner.

int getrow(char r){
        return 8-(r-'0');
}
int getcol(char c){
    return c-'a';
}

// Check Trigger.



int checkwhiteking(char board[8][8],int row,int coloum){
    yosef=0;
    count=0;
       for(i=1;i<8-coloum;i++){
        if(board[row][coloum+i]=='R' || board[row][coloum+i]=='Q'){
            for(j=coloum+1;j<coloum+i;j++){
                if(board[row][j]=='-'||board[row][j]=='.') count++;
            }
            count++;
            if(count==abs(coloum-(coloum+i))){
                yosef++;
                pos_w[0][0] =row;
                pos_w[0][1] = coloum+i;
            }
            break;
        }
    }
    count=0;
    for(i=1;i<8-row;i++){
        if(board[row+i][coloum]=='R' || board[row+i][coloum]=='Q'){
            for(j=row+1;j<row+i;j++){
                if(board[j][coloum]=='-'||board[j][coloum]=='.') count++;
            }
            count++;
            if(count==abs(row-(row+i))){
                yosef++;
                pos_w[0][0] =row+i;
                pos_w[0][1] = coloum;
            }
            break;
        }

    }
    count=0;
    for(i=1;i<=coloum;i++){
        if(board[row][coloum-i]=='R'||board[row][coloum-i]=='Q'){
            for(j=coloum-1;j>coloum-i;j--){
                if(board[row][j]=='-'||board[row][j]=='.') count++;
            }
            count++;
            if(count==abs(coloum-(coloum-i))){
                yosef++;
                pos_w[0][0]=row;
                pos_w[0][0]=coloum-i;
            }
        }
    }
    count=0;
    for(i=1;i<=row;i++){
        if(board[row-i][coloum]=='R'||board[row-i][coloum]=='Q'){
            for(j=row-1;j>row-i;j--){
                if(board[j][coloum]=='-'||board[j][coloum]=='.') count++;
            }
            count++;
            if(count==abs(row-(row-i))){
                yosef++;
                pos_w[0][0]=row-i;
                pos_w[0][0]=coloum;
            }
        }
    }

    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum+i+1]=='B' || board[row-i-1][coloum+i+1]=='Q'){
                int    B = row-i-1;

            for(j=0;j<i;j++){
                if(board[row-j-1][coloum+j+1]=='-' || board[row-j-1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_w[0][0]=row-i-1;pos_w[0][1]=coloum+i+1;n+=1;
                yosef ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum-i-1]=='B' || board[row-i-1][coloum-i-1]=='Q'){
                int    B = row-i-1;

            for(j=0;j<i;j++){
                if(board[row-j-1][coloum-j-1]=='-' || board[row-j-1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_w[0][0]=row-i-1;pos_w[0][1]=coloum-i-1;
                yosef ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum+i+1]=='B' || board[row+i+1][coloum+i+1]=='Q'){
                int    B = row+i+1;

            for(j=0;j<i;j++){
                if(board[row+j+1][coloum+j+1]=='-' || board[row+j+1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_w[0][0]=row+i+1;pos_w[0][1]=coloum+i+1;
                yosef ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum-i-1]=='B' || board[row+i+1][coloum-i-1]=='Q'){
                int    B = row+i+1;

            for(j=0;j<i;j++){
                if(board[row+j+1][coloum-j-1]=='-' || board[row+j+1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                pos_w[0][0]=row+i+1;pos_w[0][1]=coloum-i-1;
                                yosef ++;

            }
            break;
        }
    }
    count = 0;

    if(board[row+2][coloum+1]=='N'){pos_w[0][0]=row+2;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row+2][coloum-1]=='N'){pos_w[0][0]=row+2;pos_w[0][1]=coloum-1;yosef++;}
    if(board[row-2][coloum+1]=='N'){pos_w[0][0]=row-2;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row-2][coloum-1]=='N'){pos_w[0][0]=row-2;pos_w[0][1]=coloum-1;yosef++;}
    if(board[row+1][coloum+2]=='N'){pos_w[0][0]=row+1;pos_w[0][1]=coloum+2;yosef++;}
    if(board[row+1][coloum-2]=='N'){pos_w[0][0]=row+1;pos_w[0][1]=coloum-2;yosef++;}
    if(board[row-1][coloum+2]=='N'){pos_w[0][0]=row-1;pos_w[0][1]=coloum+2;yosef++;}
    if(board[row-1][coloum-2]=='N'){pos_w[0][0]=row-1;pos_w[0][1]=coloum-2;yosef++;}
    if(board[row-1][coloum+1] == 'P'&&coloum<7&&row>=1){pos_w[0][0]=row-1;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row-1][coloum-1] == 'P'){pos_w[0][0]=row-1;pos_w[0][1]=coloum-1;yosef++;}
    if(board[row+1][coloum+1] == 'K'){pos_w[0][0]=row+1;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row+1][coloum-1] == 'K'){pos_w[0][0]=row+1;pos_w[0][1]=coloum-1;yosef++;}
    if(board[row-1][coloum+1] == 'K'){pos_w[0][0]=row-1;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row-1][coloum-1] == 'K'){pos_w[0][0]=row-1;pos_w[0][1]=coloum-1;yosef++;}
    if(board[row+1][coloum] == 'K'){pos_w[0][0]=row+1;pos_w[0][1]=coloum;yosef++;}
    if(board[row-1][coloum] == 'K'){pos_w[0][0]=row-1;pos_w[0][1]=coloum;yosef++;}
    if(board[row][coloum+1] == 'K'){pos_w[0][0]=row;pos_w[0][1]=coloum+1;yosef++;}
    if(board[row][coloum-1] == 'K'){pos_w[0][0]=row;pos_w[0][1]=coloum-1;yosef++;}

    return yosef;
}
int checkblackking(char board[8][8],int row,int coloum){
    yosef2 = 0;
    count=0;
    for(i=1;i<8-coloum;i++){
        if(board[row][coloum+i]=='r' || board[row][coloum+i]=='q'){
            for(j=coloum+1;j<coloum+i;j++){
                if(board[row][j]=='-'||board[row][j]=='.') count++;
            }
            count++;
            if(count==abs(coloum-(coloum+i))){
                yosef2++;
                pos_b[0][0] =row;
                pos_b[0][1] = coloum+i;
            }
            break;
        }
    }
    count=0;
    for(i=1;i<8-row;i++){
        if(board[row+i][coloum]=='r' || board[row+i][coloum]=='q'){
            for(j=row+1;j<row+i;j++){
                if(board[j][coloum]=='-'||board[j][coloum]=='.') count++;
            }
            count++;
            if(count==abs(row-(row+i))){
                yosef2++;
                pos_b[0][0] =row+i;
                pos_b[0][1] = coloum;
            }
            break;
        }

    }
    count=0;
    for(i=1;i<=coloum;i++){
        if(board[row][coloum-i]=='r'||board[row][coloum-i]=='q'){
            for(j=coloum-1;j>coloum-i;j--){
                if(board[row][j]=='-'||board[row][j]=='.') count++;
            }
            count++;
            if(count==abs(coloum-(coloum-i))){
                yosef2++;
                pos_b[0][0]=row;
                pos_b[0][0]=coloum-i;
            }
        }
    }
    count=0;
    for(i=1;i<=row;i++){
        if(board[row-i][coloum]=='r'||board[row-i][coloum]=='q'){
            for(j=row-1;j>row-i;j--){
                if(board[j][coloum]=='-'||board[j][coloum]=='.') count++;
            }
            count++;
            if(count==abs(row-(row-i))){
                yosef2++;
                pos_b[0][0]=row-i;
                pos_b[0][0]=coloum;
            }
        }
    }
     count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum+i+1]=='b' || board[row-i-1][coloum+i+1]=='q'){
                int    B = row-i-1;

            for(j=0;j<i;j++){
                if(board[row-j-1][coloum+j+1]=='-' || board[row-j-1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_b[0][0]=row-i-1;pos_b[0][1]=coloum+i+1;n+=1;
                yosef2 ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum-i-1]=='b' || board[row-i-1][coloum-i-1]=='q'){
                int    B = row-i-1;

            for(j=0;j<i;j++){
                if(board[row-j-1][coloum-j-1]=='-' || board[row-j-1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_b[0][0]=row-i-1;pos_b[0][1]=coloum-i-1;
                yosef2 ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum+i+1]=='b' || board[row+i+1][coloum+i+1]=='q'){
                int    B = row+i+1;

            for(j=0;j<i;j++){
                if(board[row+j+1][coloum+j+1]=='-' || board[row+j+1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                    pos_b[0][0]=row+i+1;pos_b[0][1]=coloum+i+1;
                yosef2 ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum-i-1]=='b' || board[row+i+1][coloum-i-1]=='q'){
                int    B = row+i+1;

            for(j=0;j<i;j++){
                if(board[row+j+1][coloum-j-1]=='-' || board[row+j+1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                pos_b[0][0]=row+i+1;pos_b[0][1]=coloum-i-1;
                                yosef2 ++;

            }
            break;
        }
    }


    if(board[row+2][coloum+1]=='n'){pos_b[0][0]=row+2;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row+2][coloum-1]=='n'){pos_b[0][0]=row+2;pos_b[0][1]=coloum-1;yosef2++;}
    if(board[row-2][coloum+1]=='n'){pos_b[0][0]=row-2;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row-2][coloum-1]=='n'){pos_b[0][0]=row-2;pos_b[0][1]=coloum-1;yosef2++;}
    if(board[row+1][coloum+2]=='n'){pos_b[0][0]=row+1;pos_b[0][1]=coloum+2;yosef2++;}
    if(board[row+1][coloum-2]=='n'){pos_b[0][0]=row+1;pos_b[0][1]=coloum-2;yosef2++;}
    if(board[row-1][coloum+2]=='n'){pos_b[0][0]=row-1;pos_b[0][1]=coloum+2;yosef2++;}
    if(board[row-1][coloum-2]=='n'){pos_b[0][0]=row-1;pos_b[0][1]=coloum-2;yosef2++;}
    if(board[row+1][coloum+1] == 'p'){pos_b[0][0]=row+1;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row+1][coloum-1] == 'p'){pos_b[0][0]=row+1;pos_b[0][1]=coloum-1;yosef2++;}
    if(board[row+1][coloum+1] == 'k'){pos_b[0][0]=row+1;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row+1][coloum-1] == 'k'){pos_b[0][0]=row+1;pos_b[0][1]=coloum-1;yosef2++;}
    if(board[row-1][coloum+1] == 'k'){pos_b[0][0]=row-1;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row-1][coloum-1] == 'k'){pos_b[0][0]=row-1;pos_b[0][1]=coloum-1;yosef2++;}
    if(board[row+1][coloum] == 'k'){pos_b[0][0]=row+1;pos_b[0][1]=coloum;yosef2++;}
    if(board[row-1][coloum] == 'k'){pos_b[0][0]=row-1;pos_b[0][1]=coloum;yosef2++;}
    if(board[row][coloum+1] == 'k'){pos_b[0][0]=row;pos_b[0][1]=coloum+1;yosef2++;}
    if(board[row][coloum-1] == 'k'){pos_b[0][0]=row;pos_b[0][1]=coloum-1;yosef2++;}

     return yosef2;

}

int checkblack(char board[8][8],int row,int coloum){
    n = 0;
    for( i = row+1;i<8;i++){
        if(board[i][coloum] == 'r' || board[i][coloum] == 'q'){
                temp = i;
            for( j = row +1; j<i;j++){
             if(board[j][coloum] == '-' || board[j][coloum] == '.')
                count++;
            }
            count++;
            if(count == abs(row-temp)){
                n++;
            }

            break;
        }
    }
    count =0;
    for( i = row-1;i>-1;i--){
        if(board[i][coloum] == 'r' || board[i][coloum] == 'q'){
                temp = i;
            for( j = coloum-1 ; j>i;j--){
                if(board[j][coloum] == '-' || board[j][coloum] == '.' )
                    count ++;
                }
                count++;
            if(count == abs(row-temp)){
                n ++;}
                break;
        }

    }

    count = 0;
    for(i = coloum-1;i>-1;i--){
        if(board[row][i] == 'r' || board[row][i] == 'q'){
            temp = i;
            for(j = coloum-1;j>=i;j--){
                if(board[row][j] == '-' || board[row][j] == '.')
                    count ++;
            }
            count++;
                if(count == abs(coloum-temp)){
                    n++;
                }
            break;

        }
    }

    count = 0;
   for(i = coloum+1;i<8; i++){
        if(board[row][i] == 'r' || board[row][i] == 'q'){
            temp = i;
            for(j = coloum+1;i>j;j++){
                if(board[row][j] == '-' || board[row][j] == '.')
                    count ++;
            }
            count++;
                if(count == abs(coloum-temp)){
                    n ++;}
                    break;

        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum+i+1]=='b' || board[row-i-1][coloum+i+1]=='q'){
                int    B = row-i-1;
            for(j=0;j<i;j++){
                if(board[row-j-1][coloum+j+1]=='-' || board[row-j-1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum-i-1]=='b' || board[row-i-1][coloum-i-1]=='q'){
                int    B = row-i-1;
            for(j=0;j<i;j++){
                if(board[row-j-1][coloum-j-1]=='-' || board[row-j-1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum+i+1]=='b' || board[row+i+1][coloum+i+1]=='q'){
                int    B = row+i+1;
            for(j=0;j<i;j++){
                if(board[row+j+1][coloum+j+1]=='-' || board[row+j+1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum-i-1]=='b' || board[row+i+1][coloum-i-1]=='q'){
                int    B = row+i+1;
            for(j=0;j<i;j++){
                if(board[row+j+1][coloum-j-1]=='-' || board[row+j+1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;

            }
            break;
        }
    }
    if(board[row+2][coloum+1]=='n') n++;
    if(board[row+2][coloum-1]=='n') n++;
    if(board[row-2][coloum+1]=='n') n++;
    if(board[row-2][coloum-1]=='n') n++;
    if(board[row+1][coloum+2]=='n') n++;
    if(board[row+1][coloum-2]=='n') n++;
    if(board[row-1][coloum+2]=='n') n++;
    if(board[row-1][coloum-2]=='n') n++;
    if(board[row+1][coloum] == 'p') n++;
    if(board[row+2][coloum] == 'p'&&row==4) n++;

     return n;

}
int checkwhite(char board[8][8],int row,int coloum){
    n = 0;
    for( i = row+1;i<8;i++){
        if(board[i][coloum] == 'R' || board[i][coloum] == 'Q'){
                temp = i;
            for( j = row +1; j<i;j++){
             if(board[j][coloum] == '-' || board[j][coloum] == '.')
                count++;
            }
            count++;
            if(count == abs(row-temp)){
                n++;
            }

            break;
        }
    }
    count =0;
    for( i = row-1;i>-1;i--){
        if(board[i][coloum] == 'R' || board[i][coloum] == 'Q'){
                temp = i;
            for( j = coloum-1 ; j>i;j--){
                if(board[j][coloum] == '-' || board[j][coloum] == '.' )
                    count ++;
                }
                count++;
            if(count == abs(row-temp)){
                n ++;}
                break;
        }

    }

    count = 0;
    for(i = coloum-1;i>-1;i--){
        if(board[row][i] == 'R' || board[row][i] == 'Q'){
            temp = i;
            for(j = coloum-1;j>=i;j--){
                if(board[row][j] == '-' || board[row][j] == '.')
                    count ++;
            }
            count++;
                if(count == abs(coloum-temp)){
                    n++;
                }
            break;

        }
    }

    count = 0;
   for(i = coloum+1;i<8; i++){
        if(board[row][i] == 'R' || board[row][i] == 'Q'){
            temp = i;
            for(j = coloum+1;i>j;j++){
                if(board[row][j] == '-' || board[row][j] == '.')
                    count ++;
            }
            count++;
                if(count == abs(coloum-temp)){
                    n ++;}
                    break;

        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum+i+1]=='B' || board[row-i-1][coloum+i+1]=='Q'){
                int    B = row-i-1;
            for(j=0;j<i;j++){
                if(board[row-j-1][coloum+j+1]=='-' || board[row-j-1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row-i-1][coloum-i-1]=='B' || board[row-i-1][coloum-i-1]=='Q'){
                int    B = row-i-1;
            for(j=0;j<i;j++){
                if(board[row-j-1][coloum-j-1]=='-' || board[row-j-1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum+i+1]=='B' || board[row+i+1][coloum+i+1]=='Q'){
                int    B = row+i+1;
            for(j=0;j<i;j++){
                if(board[row+j+1][coloum+j+1]=='-' || board[row+j+1][coloum+j+1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;
            }
            break;
        }
    }
    count = 0;
    for(i=0;i<8;i++){
        if(board[row+i+1][coloum-i-1]=='B' || board[row+i+1][coloum-i-1]=='Q'){
                int    B = row+i+1;
            for(j=0;j<i;j++){
                if(board[row+j+1][coloum-j-1]=='-' || board[row+j+1][coloum-j-1]=='.')
                    count++;
            }
            count++;
            if(count == abs(row-B)){
                n ++;

            }
            break;
        }
    }
    if(board[row+2][coloum+1]=='N') n++;
    if(board[row+2][coloum-1]=='N') n++;
    if(board[row-2][coloum+1]=='N') n++;
    if(board[row-2][coloum-1]=='N') n++;
    if(board[row+1][coloum+2]=='N') n++;
    if(board[row+1][coloum-2]=='N') n++;
    if(board[row-1][coloum+2]=='N') n++;
    if(board[row-1][coloum-2]=='N') n++;
    if(board[row+1][coloum] == 'P') n++;
    if(board[row+2][coloum] == 'P'&&row==4) n++;

     return n;

}



int zeyad1(char board[8][8],char col[8][8]){
    int n1=pos_white_king[0][0];
    int n2=pos_white_king[0][1];
    int zoz=0;
    if(!islower(board[n1+1][n2])&&n1>=0&&n1<=6){
        board[n1+1][n2]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]+=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1+1][n2] = col[n1][n2];
        pos_white_king[0][0]-=1;
    }
    if(!islower(board[n1-1][n2])&&n1>=1&&n1<=7){
        board[n1-1][n2]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]-=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1-1][n2] = col[n1][n2];
        pos_white_king[0][0]+=1;
    }
     if(!islower(board[n1][n2+1])&&n2>=0&&n2<=6){
        board[n1][n2+1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][1]+=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1][n2+1] = col[n1][n2];
        pos_white_king[0][1]-=1;
    }
     if(!islower(board[n1][n2-1])&&n2>=1&&n1<=7){
        board[n1][n2-1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][1]-=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1][n2-1] = col[n1][n2];
        pos_white_king[0][1]+=1;
    }
     if(!islower(board[n1+1][n2+1])&&n1>=0&&n1<=6&&n2>=0&&n2<=6){
        board[n1+1][n2+1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]+=1;
        pos_white_king[0][1]+=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1+1][n2+1] = col[n1][n2];
        pos_white_king[0][0]-=1;
        pos_white_king[0][1]-=1;
    }
     if(!islower(board[n1+1][n2-1])&&n1>=0&&n1<=6&&n2>=1&&n2<=7){
        board[n1+1][n2-1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]+=1;
        pos_white_king[0][1]-=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1+1][n2+1] = col[n1+1][n2+1];
        pos_white_king[0][0]-=1;
        pos_white_king[0][1]+=1;
    }
     if(!islower(board[n1-1][n2+1])&&n1>=1&&n1<=7&&n2>=0&&n2<=6){
        board[n1-1][n2+1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]-=1;
        pos_white_king[0][1]+=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        pos_white_king[0][0]+=1;
        pos_white_king[0][1]-=1;
        board[pos_white_king[0][0]][ pos_white_king[0][1]] = 'k';
        board[n1-1][n2+1] = col[n1-1][n2+1];

    }
     if(!islower(board[n1-1][n2-1])&&n1>=1&&n1<=7&&n2>=1&&n2<=7){
        board[n1-1][n2-1]='k';
        board[n1][n2] = col[n1][n2];
        pos_white_king[0][0]-=1;
        pos_white_king[0][1]-=1;
        if(!checkwhiteking(board,pos_white_king[0][0],pos_white_king[0][1])) zoz=1;
        board[n1][n2] = 'k';
        board[n1-1][n2-1] = col[n1][n2];
        pos_white_king[0][0]+=1;
        pos_white_king[0][1]+=1;
    }
    return zoz;
}
int zeyad2(char board[8][8],char col[8][8]){
    int n1=pos_black_king[0][0];
    int n2=pos_black_king[0][1];
    int zoz2=0;
    if(!isupper(board[n1+1][n2])&&n1>=0&&n1<=6){
        board[n1+1][n2]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]+=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1+1][n2] = col[n1][n2];
        pos_black_king[0][0]-=1;
    }
    if(!isupper(board[n1-1][n2])&&n1>=1&&n1<=7){
        board[n1-1][n2]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]-=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1-1][n2] = col[n1][n2];
        pos_black_king[0][0]+=1;
    }
     if(!isupper(board[n1][n2+1])&&n2>=0&&n2<=6){
        board[n1][n2+1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][1]+=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1][n2+1] = col[n1][n2];
        pos_black_king[0][1]-=1;
    }
     if(!isupper(board[n1][n2-1])&&n2>=1&&n2<=7){
        board[n1][n2-1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][1]-=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1][n2-1] = col[n1][n2];
        pos_black_king[0][1]+=1;
    }
     if(!isupper(board[n1+1][n2+1])&&n1>=0&&n1<=6&&n2>=0&&n2<=6){
        board[n1+1][n2+1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]+=1;
        pos_black_king[0][1]+=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'k';
        board[n1+1][n2+1] = col[n1][n2];
        pos_black_king[0][0]-=1;
        pos_black_king[0][1]-=1;
    }
     if(!isupper(board[n1+1][n2-1])&&n1>=0&&n1<=6&&n2>=1&&n2<=7){
        board[n1+1][n2-1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]+=1;
        pos_black_king[0][1]-=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1+1][n2+1] = col[n1][n2];
        pos_black_king[0][0]-=1;
        pos_black_king[0][1]+=1;
    }
     if(!isupper(board[n1-1][n2+1])&&n1>=1&&n1<=7&&n2>=0&&n2<=6){
        board[n1-1][n2+1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]-=1;
        pos_black_king[0][1]+=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1-1][n2+1] = col[n1][n2];
        pos_black_king[0][0]+=1;
        pos_black_king[0][1]-=1;
    }
     if(!isupper(board[n1-1][n2-1])&&n1>=1&&n1<=7&&n2>=1&&n2<=7){
        board[n1-1][n2-1]='K';
        board[n1][n2] = col[n1][n2];
        pos_black_king[0][0]-=1;
        pos_black_king[0][1]-=1;
        if(!checkblackking(board,pos_black_king[0][0],pos_black_king[0][1])) zoz2++;
        board[n1][n2] = 'K';
        board[n1-1][n2-1] = col[n1][n2];
        pos_black_king[0][0]+=1;
        pos_black_king[0][1]+=1;
    }
    return zoz2;
}
int num=0;

int checkremovewhite(char board[8][8]){
    int num = 0;
    if(abs(pos_white_king[0][0]-pos_w[0][0]) == abs(pos_white_king[0][0]-pos_w[0][0])){
        if(pos_white_king[0][0]>pos_w[0][0]&&pos_white_king[0][1]<pos_w[0][1]){
            for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]-i,pos_white_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_white_king[0][0]>pos_w[0][0]&&pos_white_king[0][1]>pos_w[0][1]){
            for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]-i,pos_white_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_white_king[0][0]<pos_w[0][0]&&pos_white_king[0][1]<pos_w[0][1]){
            for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]+i,pos_white_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_white_king[0][0]<pos_w[0][0]&&pos_white_king[0][1]>pos_w[0][1]){
            for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]+i,pos_white_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }
    }
    if((pos_white_king[0][0]==pos_w[0][0]&&abs(pos_white_king[0][1]-pos_w[0][1])!=0)||(pos_white_king[0][1]==pos_w[0][1]&&abs(pos_white_king[0][0]-pos_w[0][0])!=0)){
        if(pos_w[0][1]==pos_white_king[0][1]&&pos_white_king[0][0]>pos_w[0][0]){
               for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]-i,pos_white_king[0][1])){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_w[0][1]==pos_white_king[0][1]&&pos_white_king[0][0]<pos_w[0][0]){
               for(i=1;i<abs(pos_white_king[0][0]-pos_w[0][0]);i++){
                if(checkblack(board,pos_white_king[0][0]+i,pos_white_king[0][1])){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_w[0][0]==pos_white_king[0][0]&&pos_white_king[0][1]<pos_w[0][1]){
               for(i=1;i<abs(pos_white_king[0][1]-pos_w[0][1]);i++){
                if(checkblack(board,pos_white_king[0][0],pos_white_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
         else if(pos_w[0][0]==pos_white_king[0][0]&&pos_white_king[0][1]>pos_w[0][1]){
               for(i=1;i<abs(pos_white_king[0][1]-pos_w[0][1]);i++){
                if(checkblack(board,pos_white_king[0][0],pos_white_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }


    }
    return num;
}

int checkremoveblack(char board[8][8]){
    int num = 0;
    if(abs(pos_black_king[0][0]-pos_b[0][0]) == abs(pos_black_king[0][0]-pos_b[0][0])){
        if(pos_black_king[0][0]>pos_b[0][0]&&pos_black_king[0][1]<pos_b[0][1]){
            for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]-i,pos_black_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_black_king[0][0]>pos_b[0][0]&&pos_black_king[0][1]>pos_b[0][1]){
            for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]-i,pos_black_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_black_king[0][0]<pos_b[0][0]&&pos_black_king[0][1]<pos_b[0][1]){
            for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]+i,pos_black_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_black_king[0][0]<pos_b[0][0]&&pos_black_king[0][1]>pos_b[0][1]){
            for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]+i,pos_black_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }
    }
    if((pos_black_king[0][0]==pos_b[0][0]&&abs(pos_black_king[0][1]-pos_b[0][1])!=0)||(pos_black_king[0][1]==pos_b[0][1]&&abs(pos_black_king[0][0]-pos_b[0][0])!=0)){
        if(pos_b[0][1]==pos_black_king[0][1]&&pos_black_king[0][0]>pos_b[0][0]){
               for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]-i,pos_black_king[0][1])){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_b[0][1]==pos_black_king[0][1]&&pos_black_king[0][0]<pos_b[0][0]){
               for(i=1;i<abs(pos_black_king[0][0]-pos_b[0][0]);i++){
                if(checkwhite(board,pos_black_king[0][0]+i,pos_black_king[0][1])){
                    num = 1;
                    break;
                }
            }
        }
        else if(pos_b[0][0]==pos_black_king[0][0]&&pos_black_king[0][1]<pos_b[0][1]){
               for(i=1;i<abs(pos_black_king[0][1]-pos_b[0][1]);i++){
                if(checkwhite(board,pos_black_king[0][0],pos_black_king[0][1]+i)){
                    num = 1;
                    break;
                }
            }
        }
         else if(pos_b[0][0]==pos_black_king[0][0]&&pos_black_king[0][1]>pos_b[0][1]){
               for(i=1;i<abs(pos_black_king[0][1]-pos_b[0][1]);i++){
                if(checkwhite(board,pos_black_king[0][0],pos_black_king[0][1]-i)){
                    num = 1;
                    break;
                }
            }
        }


    }
    return num;
}

// dead position

void dead_pos(char board[8][8],char col[8][8],char displayed_white[16],char displayed_black[16])
{
    int size1=0,size2=0;
    int num1=0,num2=0;
    int w[1][2],b[1][2];
    for(i=0;i<16;i++){
        if(islower(displayed_white[i])) size1++;
        if(isupper(displayed_black[i])) size2++;
    }
    if(size1==15&&size2==15){
        printf("Dead position\n");
        exit(0);
    }
     num1=num2=0;
    if(size1==15&&size2==14){
        for(i=0;i<16;i++){
            if(displayed_black[i]=='B') num1++;
            if(displayed_black[i]=='N') num2++;
        }
        if((num1==1&&num2==2)||(num1==2&&num2==1)){
            printf("Dead position\n");
            exit(0);
        }
    }
    num1=num2=0;
    if(size1==14&&size2==15){
        for(i=0;i<16;i++){
            if(displayed_white[i]=='b') num1++;
            if(displayed_white[i]=='n') num2++;
        }
        if((num1==1&&num2==2)||(num1==2&&num2==1)){
            printf("Dead position\n");
            exit(0);
        }
    }
     num1=num2=0;
    if(size1==14&&size2==14){
       for(i=0;i<16;i++){
            if(displayed_white[i]=='b') num1++;
            if(displayed_black[i]=='B') num2++;
        }
    if(num1==1&&num2==1){
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(board[i][j]=='b') {
                    w[0][0]=i;
                    w[0][1]=j;
                }
                if(board[i][j]=='B') {
                    b[0][0]=i;
                    b[0][1]=j;
                }
            }
        }
        if((col[w[0][0]][w[0][1]]=='-'&&col[b[0][0]][b[0][1]]=='-')||(col[w[0][0]][w[0][1]]=='.'&&col[b[0][0]][b[0][1]]=='.')){
             printf("Dead position\n");
            exit(0);
        }
    }
    }


}

// Movements.

int move_w =0,move_b =0;
void black_move_remove(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16], char displayed_black[16], char A,char col[8][8]){
    int l = 0;
                 if(A == '.' || A == '-'){
                    board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                    board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                }
                else if (A == 'p' || A == 'r' || A == 'n' || A == 'b' || A == 'q' || A== 'k'){
                    displayed_white[move_w++] = A;
                    board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                    board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                }
                else{
                    printf("The move is not allowed!\n");
                    player2options(board,col,displayed_white,displayed_black);
                }

}
void white_move_remove(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16], char displayed_black[16], char A,char col[8][8]){
    int l = 0;
                if(A == '.' || A == '-'){
                    board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                    board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                }
                else if (A == 'P' || A == 'R' || A == 'N' || A == 'B' || A == 'Q' || A=='K'){

                    displayed_black[move_b++] = A;
                    board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                    board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                }
                else{
                    printf("The move is not allowed!\n");
                    player1options(board,col,displayed_white,displayed_black);
                    }

}

// Movements itself.

void pawn_promotion(char board[8][8],char fr,char fc,char sr,char sc,char white_promotion[4],char black_promotion[4]){
    if(getrow(sr) == getrow('8') && board[getrow(fr)][getcol(fc) == 'p']){

        for(int i =0;i<4;i++)
            printf("[%d] %c    ",i+1,white_promotion[i]);
        char pawn;
        printf("\nChoose which piece to promote to: ");
        do{
                pawn = getchar();
        } while(!(pawn == '1' || pawn == '2' || pawn == '3' || pawn == '4'));
        switch(pawn)
        {
        case '1':
            board[getrow('8')][getcol(sc)] = 'q';
            break;
        case '2':
            board[getrow('8')][getcol(sc)] = 'r';
            break;
        case '3':
            board[getrow('8')][getcol(sc)] = 'b';
            break;
        case '4':
            board[getrow('8')][getcol(sc)] = 'n';
            break;
        default:
            printf("Invalid Value!");
            pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
        }
    }
    else if(getrow(sr) == getrow('1') && board[getrow(fr)][getcol(fc) == 'P']){
        for(int i =0;i<4;i++)
            printf("[%d] %c    ",i+1,black_promotion[i]);
        char pawn;
        printf("\nChoose which piece to promote to: ");
        do{
                pawn = getchar();
        } while(!(pawn == '1' || pawn == '2' || pawn == '3' || pawn == '4'));
        switch(pawn)
        {
        case '1':
            board[getrow('1')][getcol(sc)] = 'Q';
            break;
        case '2':
            board[getrow('1')][getcol(sc)] = 'R';
            break;
        case '3':
            board[getrow('1')][getcol(sc)] = 'B';
            break;
        case '4':
            board[getrow('1')][getcol(sc)] = 'N';
            break;
        default:
            printf("Invalid Value!");
            pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
        }
    }
}
void pawn_black_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8],char white_promotion[4],char black_promotion[4]){
    int k=0,l=0;

            if(fr != '7'){
                if((getrow(sr) == getrow(fr)+1) && (getcol(fc) == getcol(sc))){
                        if((board[getrow(fr)+1][getcol(fc)] == '.' || board[getrow(fr)+1][getcol(fc)] == '-')){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);


                        }
                    }
                   else if((getrow(sr) == getrow(fr)+1) && (getcol(fc)+1 == getcol(sc))){
                        char A = board[getrow(fr)+1][getcol(fc)+1];
                        if(A == 'p' || A == 'r' || A == 'n' || A == 'b' || A == 'q' || A == 'k'){
                        displayed_white[move_w++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                    }
                }
                else if((getrow(sr) == getrow(fr)+1) && (getcol(fc)-1 == getcol(sc))){
                        char A = board[getrow(fr)+1][getcol(fc)-1];
                        if(A == 'p' || A == 'r' || A == 'n' || A == 'b' || A == 'q' || A == 'k'){
                        displayed_white[move_w++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                    }
                }
                else {
                    printf("\nThe move is not allowed\n");
                    player2options(board,col,displayed_white,displayed_black);
                }



            }

            else if(fr == '7'){
                    if((getrow(sr) == getrow(fr)+1) && (getcol(fc) == getcol(sc))){
                        if((board[getrow(fr)+1][getcol(fc)] == '.' || board[getrow(fr)+1][getcol(fc)] == '-')){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                        }
                    }
                    else if((getrow(sr) == getrow(fr)+2) && (getcol(fc) == getcol(sc)) ){
                        if((board[getrow(fr)+2][getcol(fc)] == '.' || board[getrow(fr)+2][getcol(fc)] == '-') && (board[getrow(fr)+1][getcol(fc)] == '.' || board[getrow(fr)+1][getcol(fc)] == '-') ){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                        }
                    }
                    else if((getrow(sr) == getrow(fr)+1) && (getcol(fc)+1 == getcol(sc))){
                        char A = board[getrow(fr)+1][getcol(fc)+1];
                        displayed_white[move_w++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                    }
                }
                else if((getrow(sr) == getrow(fr)+1) && (getcol(fc)-1 == getcol(sc))){
                        char A = board[getrow(fr)+1][getcol(fc)-1];
                        if(A == 'p' || A == 'r' || A == 'n' || A == 'b' || A == 'q' || A == 'k'){
                        displayed_white[move_w++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player2options(board,col,displayed_white,displayed_black);
                    }
                }
                else {
                    printf("\nThe move is not allowed\n");
                    player2options(board,col,displayed_white,displayed_black);
                }

}
void pawn_white_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8],char white_promotion[4],char black_promotion[4]){
        int k=0,l=0;
            if(fr != '2'){
                if((getrow(sr) == getrow(fr)-1) && (getcol(fc) == getcol(sc))){
                        if((board[getrow(fr)-1][getcol(fc)] == '.' || board[getrow(fr)-1][getcol(fc)] == '-')){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];


                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                        }

                    }
               else if((getrow(sr) == getrow(fr)-1) && (getcol(fc)+1 == getcol(sc))){
                        char A = board[getrow(fr)-1][getcol(fc)+1];
                        if(A == 'P' || A == 'R' || A == 'N' || A == 'B' || A == 'Q' || A == 'K'){
                        displayed_black[move_b++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                    }
                }
                else if((getrow(sr) == getrow(fr)-1) && (getcol(fc)-1 == getcol(sc))){
                        char A = board[getrow(fr)-1][getcol(fc)-1];
                        if(A == 'P' || A == 'R' || A == 'N' || A == 'B' || A == 'Q' || A == 'K'){
                        displayed_black[move_b++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        pawn_promotion(board,fr,fc,sr,sc,white_promotion,black_promotion);
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                    }
                }
                else {
                    printf("\nThe move is not allowed\n");
                    player1options(board,col,displayed_white,displayed_black);
                }



            }

            else if(fr == '2'){
                    if((getrow(sr) == getrow(fr)-1) && (getcol(fc) == getcol(sc))){
                        if((board[getrow(fr)-1][getcol(fc)] == '.' || board[getrow(fr)-1][getcol(fc)] == '-')){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                        }
                    }
                    else if((getrow(sr) == getrow(fr)-2) && (getcol(fc) == getcol(sc)) ){
                        if((board[getrow(fr)-2][getcol(fc)] == '.' || board[getrow(fr)-2][getcol(fc)] == '-') && (board[getrow(fr)-1][getcol(fc)] == '.' || board[getrow(fr)-1][getcol(fc)] == '-') ){
                            board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                            board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else{
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                        }
                    }
                else if((getrow(sr) == getrow(fr)-1) && (getcol(fc)+1 == getcol(sc))){
                        char A = board[getrow(fr)-1][getcol(fc)+1];
                        if(A == 'P' || A == 'R' || A == 'N' || A == 'B' || A == 'Q' || A == 'K'){
                        displayed_black[move_b++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];

                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                    }
                }
                else if((getrow(sr) == getrow(fr)-1) && (getcol(fc)-1 == getcol(sc))){
                        char A = board[getrow(fr)-1][getcol(fc)-1];
                        if(A == 'P' || A == 'R' || A == 'N' || A == 'B' || A == 'Q' || A == 'K'){
                        displayed_black[move_b++] = A;
                        board[getrow(sr)][getcol(sc)] = board[getrow(fr)][getcol(fc)];
                        board[getrow(fr)][getcol(fc)] = col[getrow(fr)][getcol(fc)];
                        }
                        else {
                        printf("\nThe move is not allowed\n");
                        player1options(board,col,displayed_white,displayed_black);
                    }
                }
                else {
                    printf("\nThe move is not allowed\n");
                    player1options(board,col,displayed_white,displayed_black);
                }
}
}
void knights_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8], int indicator){
     int k=0,l=0;
             if(abs(getrow(sr)-getrow(fr))==2 && abs(getcol(sc)-getcol(fc))==1 ){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'N')
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else if(abs(getrow(sr)-getrow(fr))==1 && abs(getcol(sc)-getcol(fc))==2 ){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'N')
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
                printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
            }


}
void Rooks_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8],int indicator){
    int i = 0,k = 0,count = 0;

        if(getrow(fr) > getrow(sr) && getcol(fc)==getcol(sc)){
            for(i=getrow(fr)-1;i>getrow(sr);--i){
                if(board[i][getcol(fc)] == '-' || board[i][getcol(fc)] == '.'){
                    count++;
                }
            }
            if(count == getrow(fr) - getrow(sr) -1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] =='R' || board[getrow(fr)][getcol(fc)] =='Q'  )
                   black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else if (getrow(fr) < getrow(sr) && getcol(fc)==getcol(sc)){
            for(i=getrow(sr)-1;i>getrow(fr);--i){
                if(board[i][getcol(sc)] == '-' || board[i][getcol(sc)] == '.'){
                    count++;
                }
            }
            if(count == getrow(sr) - getrow(fr) -1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] =='R' || board[getrow(fr)][getcol(fc)] =='Q' )
                   black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else if(getrow(fr) == getrow(sr) && getcol(sc) > getcol(fc)){
            for(i=getcol(fc)+1;i<getcol(sc);i++){
                if(board[getrow(fr)][i] == '.' || board[getrow(fr)][i] == '-')
                    count = count + 1;
            }

            if(count == getcol(sc) - getcol(fc) - 1){
                char   A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'R' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else if(getrow(fr) == getrow(sr) && getcol(sc) < getcol(fc)){
            for(i=getcol(sc)+1;i<getcol(fc);i++){
                if(board[getrow(fr)][i] == '.' || board[getrow(fr)][i] == '-')
                    count = count + 1;
            }

            if(count == getcol(fc) - getcol(sc) - 1){
                char   A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'R' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
}
void Bishop_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8], int indicator){
    int i = 0,k = 0,count = 0;

        if(getrow(fr) > getrow(sr) && getcol(sc) > getcol(fc)&&(abs(getrow(fr)-getrow(sr))==abs(getcol(fc)-getcol(sc)))){
            for(i=0;i<getrow(fr)-getrow(sr)-1;++i){
                if(board[getrow(fr)-i-1][getcol(fc)+i+1] == '.' || board[getrow(fr)-i-1][getcol(fc)+i+1] == '-')
                    count++;
            }
            if(count == getrow(fr)-getrow(sr)-1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'B' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else if(getrow(fr) < getrow(sr) && getcol(sc) > getcol(fc)&&(abs(getrow(fr)-getrow(sr))==abs(getcol(fc)-getcol(sc)))){
            for(i=0;i<getrow(sr)-getrow(fr)-1;++i){
                if(board[getrow(sr)-i-1][getcol(sc)-i-1] == '.' || board[getrow(sr)-i-1][getcol(sc)-i-1] == '-')
                    count++;
            }
            if(count == getrow(sr)-getrow(fr)-1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'B' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
         else if(getrow(fr) > getrow(sr) && getcol(sc) < getcol(fc)&&(abs(getrow(fr)-getrow(sr))==abs(getcol(fc)-getcol(sc)))){
            for(i=0;i<getrow(fr)-getrow(sr)-1;++i){
                if(board[getrow(fr)-i-1][getcol(fc)-i-1] == '.' || board[getrow(fr)-i-1][getcol(fc)-i-1] == '-')
                    count++;
            }
            if(count == getrow(fr)-getrow(sr)-1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'B' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else if(getrow(fr) < getrow(sr) && getcol(sc) < getcol(fc)&&(abs(getrow(fr)-getrow(sr))==abs(getcol(fc)-getcol(sc)))){
            for(i=0;i<getrow(sr)-getrow(fr)-1;++i){
                if(board[getrow(fr)+i+1][getcol(fc)-i-1] == '.' || board[getrow(fr)+i+1][getcol(fc)-i-1] == '-')
                    count++;
            }
            if(count == getrow(sr)-getrow(fr)-1){
                char A = board[getrow(sr)][getcol(sc)];
                if(board[getrow(fr)][getcol(fc)] == 'B' || board[getrow(fr)][getcol(fc)] =='Q' )
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
                else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);

            }
            else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
        }
        else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}

}

void queen_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8], int indicator){
    int i = 0,k = 0,count = 0;
        if(getrow(fr) == getrow(sr) || getcol(fc) == getcol(sc))
            Rooks_movements(board,fr,fc,sr,sc,displayed_white,displayed_black,col,indicator);
        else if(abs(getrow(sr)-getrow(fr)) == abs(getcol(sc)-getcol(fc)))
            Bishop_movements(board,fr,fc,sr,sc,displayed_white,displayed_black,col,indicator);
        else{
            printf("\nThe move is not allowed\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
}
}
void king_movements(char board[8][8],char fr,char fc,char sr,char sc,char displayed_white[16],char displayed_black[16],char col[8][8], int indicator){
    int k = 0;
    if((abs(getcol(sc)-getcol(fc))==1 && getrow(fr) == getrow(sr) )|| ((abs(getrow(fr)-getrow(sr))==1 && getcol(sc)==getcol(fc)))){
        char A = board[getrow(sr)][getcol(sc)];
        if(board[getrow(fr)][getcol(fc)] == 'K')
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
        else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
    }
    else if(abs(getcol(sc)-getcol(fc))==1 && abs(getrow(fr)-getrow(sr))==1 ){
        char A = board[getrow(sr)][getcol(sc)];
        if(board[getrow(fr)][getcol(fc)] == 'K')
                    black_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
        else
                    white_move_remove(board,fr,fc,sr,sc,displayed_white,displayed_black,A,col);
    }
    else{
            printf("\nThe move is not allowed**\n");
                if(indicator == 1)
                {
                    player1options(board,col,displayed_white,displayed_black);
                }
                else if(indicator == 2)
                {
                    player2options(board,col,displayed_white,displayed_black);
                }
    }

}


// Moves Counter.
int movecount(int indicator){
    if(indicator == 1)
        counter1++;
    else if(indicator == 2)
        counter2++;
}


//------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------//

// Interface.
void printboard(char board[8][8]){
    system("cls");
    printf("   ");
    for(int i=0;i<8;i++){
        printf("%c ",i+65);
    }
    printf("\n");

    for(int i =0;i<8;i++){
            printf("%d  ",8-i);

            for(int j=0;j<8;j++){
                        if (islower(board[i][j]) || board[i][j] == '.')
                        {
                            printf("\033[1;31m");
                            printf("%c ",board[i][j]);
                            printf("\033[0m");
                        }
                        else if (isupper(board[i][j]) || board[i][j] == '-')
                        {
                            printf("\033[1;34m");
                            printf("%c ",board[i][j]);
                            printf("\033[0m");
                        }
                    }
                    printf(" %d",8-i);
                    printf("\n");
                 };
                    printf("   ");
                 for(int i=0;i<8;i++){
                    printf("%c ",i+65);
                 }
                 printf("\n");
                 printf("   ");
}
void chBoard(char board[8][8], char col[8][8], char displayed_white[16], char displayed_black[16], int player_indicator)
{
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    fakeboard[i][j] = board[i][j];
                }
            }

    char fcol, frow;
    char srow,scol;
    printf("\nType your inputs noting that only small letters are allowed.");
    if(player_indicator == 1)
    {
        printf("\033[1;31m");
        printf("\nPiece Place (<Column Letter><Row Number>): ");
        scanf(" %c%c", &fcol, &frow);
        printf("Move to (<Column Letter><Row Number>): ");
        scanf(" %c%c",&scol,&srow);
        printf("\033[0m");
    }
    else if(player_indicator == 2)
    {
        printf("\033[1;34m");
        printf("\nPiece Place (<Column Letter><Row Number>): ");
        scanf(" %c%c", &fcol, &frow);
        printf("Move to (<Column Letter><Row Number>): ");
        scanf(" %c%c",&scol,&srow);
        printf("\033[0m");
    }
    char white_promotion[4] = {'q','r','b','n'};
    char black_promotion[4] = {'Q','R','B','N'};

    if(player_indicator == 1)
    {
        switch(fakeboard[getrow(frow)][getcol(fcol)]){
        case 'p' :
            pawn_white_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,white_promotion,black_promotion);
            break;
        case 'n':
            knights_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'r' :
            Rooks_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'b' :
            Bishop_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'q' :
            queen_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'k' :
            king_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            pos_white_king[0][0]=getrow(srow);
            pos_white_king[0][1]=getcol(scol);

            break;
        default:
            printboard(board);
            printf("Invalid Entry!\n");
            player1options(board,col,displayed_white,displayed_black);
        }
         if (checkwhiteking(fakeboard,pos_white_king[0][0],pos_white_king[0][1]) == 0)
        {
            for ( i = 0; i < 8; i++){
                for ( j = 0; j < 8; j++){
                    board[i][j] = fakeboard[i][j];
                }
            }
            printboard(board);

        }
        else if (checkwhiteking(fakeboard,pos_white_king[0][0],pos_white_king[0][1]) != 0)
        {

            printboard(board);
            printf("\nNot a valid move.");
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if(board[i][j]=='k'){
                        pos_white_king[0][0]=i;
                        pos_white_king[0][1]=j;
                }
            }
        }

            player1options(board,col,displayed_white,displayed_black);
        }
    }
     else if(player_indicator == 2)
    {
     switch(fakeboard[getrow(frow)][getcol(fcol)]){
        case 'P' :
            pawn_black_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,white_promotion,black_promotion);
            break;
        case 'N':
            knights_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'R' :
            Rooks_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'B' :
            Bishop_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'Q' :
            queen_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            break;
        case 'K' :
            king_movements(fakeboard,frow,fcol,srow,scol,displayed_white,displayed_black,col,player_indicator);
            pos_black_king[0][0]=getrow(srow);
            pos_black_king[0][1]=getcol(scol);

            break;
        default:
            printboard(board);
            printf("Invalid Entry!\n");
            player2options(board,col,displayed_white,displayed_black);
        }
        if (checkblackking(fakeboard,pos_black_king[0][0],pos_black_king[0][1]) == 0)
        {
            for ( i = 0; i < 8; i++){
                for ( j = 0; j < 8; j++){
                    board[i][j] = fakeboard[i][j];
                }
            }
            printboard(board);

        }
        else if (checkblackking(fakeboard,pos_black_king[0][0],pos_black_king[0][1]) != 0)
        {
            printboard(board);
            printf("\nNot a valid move.");
            for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(board[i][j]=='K'){
                    pos_black_king[0][0]=i;
                    pos_black_king[0][1]=j;
                }
            }
        }

            player2options(board,col,displayed_white,displayed_black);
        }
    }

    // Printing the board after moving the piece.
    printf("\nRemoved White Pieces\n");
    for(int i=0;i<16;i++){
        printf("%c ", displayed_white[i]);
    }
    printf("\nRemoved Black Pieces\n");
    for(int i=0;i<16;i++){
        printf("%c ", displayed_black[i]);
    }
    printf("\n");
    printf("%d\t%d\n",pos_white_king[0][0],pos_white_king[0][1]);
    printf("%d\t%d\n",pos_black_king[0][0],pos_black_king[0][1]);


}

int reda=0;

int st_w(char board[8][8]){
    reda = 0;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(board[i][j]=='p'){
                if(!isupper(board[i-1][j-1])&&!isupper(board[i-1][j+1])&&(board[i-1][j]!='-'||board[i-1][j]!='.')) reda++;
            }
            if(board[i][j]=='n'){
                if(islower(board[i+2][j+1])&&islower(board[i+2][j-1])&&islower(board[i-2][j+1])&&islower(board[i-2][j-1])){
                    if(islower(board[i+1][j+2])&&islower(board[i+1][j-2])&&islower(board[i-1][j+2])&&islower(board[i-1][j-2]))
                        reda ++;
                }
            }
            if(board[i][j]=='r'||board[i][j]=='q'){
                if(islower(board[i+1][j])&&islower(board[i-1][j])&&islower(board[i][j+1])&&islower(board[i][j-1]))
                    reda++;
            }
            if(board[i][j]=='b'||board[i][j]=='q'){
                 if(islower(board[i+1][j+1])&&islower(board[i+1][j-1])&&islower(board[i-1][j+1])&&islower(board[i-1][j-1]))
                    reda++;
            }
        }
    }
    return reda;
}

int st_b(char board[8][8]){
    reda = 0;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(board[i][j]=='P'){
                if(!isupper(board[i+1][j-1])&&!isupper(board[i-1][j+1])&&(board[i+1][j]!='-'||board[i+1][j]!='.')) reda++;
            }
            if(board[i][j]=='N'){
                if(islower(board[i+2][j+1])&&islower(board[i+2][j-1])&&islower(board[i-2][j+1])&&islower(board[i-2][j-1])){
                    if(islower(board[i+1][j+2])&&islower(board[i+1][j-2])&&islower(board[i-1][j+2])&&islower(board[i-1][j-2]))
                        reda ++;
                }
            }
            if(board[i][j]=='R'||board[i][j]=='Q'){
                if(islower(board[i+1][j])&&islower(board[i-1][j])&&islower(board[i][j+1])&&islower(board[i][j-1]))
                    reda++;
            }
            if(board[i][j]=='B'||board[i][j]=='Q'){
                 if(islower(board[i+1][j+1])&&islower(board[i+1][j-1])&&islower(board[i-1][j+1])&&islower(board[i-1][j-1]))
                    reda++;
            }
        }
    }
    return reda;
}


int player1options(char board[8][8], char col[8][8], char displayed_white[16], char displayed_black[16])
{
    PLAYER_INDICATOR = 1;
    char fakeboard[8][8];
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            fakeboard[i][j] = board[i][j];
        }
    }
    if(checkwhiteking(fakeboard,pos_white_king[0][0],pos_white_king[0][1]) != 1)
        {
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    board[i][j] = fakeboard[i][j];
                }
            }
        }
        dead_pos(board,col,displayed_white,displayed_black);

    int mo=0;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(islower(board[i][j]))
                mo++;
        }
    }
    if(mo-1==st_w(board)) {
        if(checkwhiteking(fakeboard,pos_white_king[0][0],pos_white_king[0][1]) == 0&&zeyad1(fakeboard,col)==0){
            printf("stalmate\n");
            exit(0);
        }
    }

    if(checkwhiteking(fakeboard,pos_white_king[0][0],pos_white_king[0][1]))
    {

        if(yosef==1){
            if(zeyad1(fakeboard,col)==0&&checkblackking(fakeboard,pos_w[0][0],pos_w[0][1])==0&&checkremovewhite(board)==0){
                printf("WON :D\n\n");
                exit(0);
            }
        }
        if(yosef==2){
            if(zeyad1(fakeboard,col)==0){
                printf("WON :D\n\n");
                exit(0);
            }
        }

        printf("\nWhite King is on Check!\n");


    }

    char option;
    printf("\nPLAYER [1] TURN.\t\t\t\tNumber of moves made: %d\n\nPlease select whether to:\n", counter1);
    printf("(A) Play.\t(B) Surrender.\t (C) Save.\t (D) Undo.\t (E) Redo.\n");
    printf("Type your selection here noting that only A, B, C, D or E are the accepted values: ");
    do
    {
        scanf(" %c", &option);
    }while(!(option == 'A' || option == 'B' || option == 'C'|| option == 'D' || option == 'E'));
    if(option == 'A')
    {
            if(counter1==0) saveWhitemove(board,displayed_white,displayed_black,PLAYER_INDICATOR);
            chBoard(board,col,displayed_white,displayed_black,1);
            saveBlackmove(board,displayed_white,displayed_black,PLAYER_INDICATOR);
            movecount(1);
            player2options(board,col,displayed_white,displayed_black);
            return 0;
    }
    else if(option == 'B')
    {
        printf("\nPlayer [1] surrendered!\n");
        printf("\nPress any key to exit.");
        getch();
        exit(0);
    }
    else if(option == 'C')
    {
        save(board,displayed_white,displayed_black);
        player1options(board,col,displayed_white,displayed_black);
    }
    else if(option == 'D'){
            int w=0,b=0;
        if(counter1-1>0){
            counter1-=1;
            loadWhitemove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
        }
        else if(counter1==1){
            counter1-=1;
            loadWhitemove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
        }
        else
            printf("Error\n");
        player1options(board,col,displayed_white,displayed_black);

    }
    else if(option == 'E'){

            int w=0,b=0;
            counter1++;
            itoa(counter1,ch_w,10);
            FILE *fptr;
            fptr = fopen(ch_w,"r");
            if(!(fptr==NULL)){

            loadWhitemove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);


            printf("\n");
            }
            else{
                printf("ERROR\n");
                counter1--;

            }

            player1options(board,col,displayed_white,displayed_black);



    }

}
int player2options(char board[8][8], char col[8][8], char displayed_white[16], char displayed_black[16])
{
    PLAYER_INDICATOR = 2;
   char fakeboard[8][8];
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            fakeboard[i][j] = board[i][j];
        }
    }
    if(checkblackking(fakeboard,pos_black_king[0][0],pos_black_king[0][1]) != 1)
        {
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    board[i][j] = fakeboard[i][j];
                }
            }
        }
    dead_pos(board,col,displayed_white,displayed_black);
    int mo=0;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(isupper(board[i][j]))
                mo++;
        }
    }

    if(mo-1==st_b(board)) {
        if(checkblackking(fakeboard,pos_black_king[0][0],pos_black_king[0][1]) == 0 && zeyad2(fakeboard,col)==0){
            printf("stalmate\n");
            exit(0);
        }
    }

    if(checkblackking(fakeboard,pos_black_king[0][0],pos_black_king[0][1])==1)
    {

        if(yosef2==1){
            if(zeyad2(fakeboard,col)==0&&checkwhite(fakeboard,pos_b[0][0],pos_b[0][1])==0&&checkremoveblack(board)==0){
                printf("WON :D\n\n");
                exit(0);
            }
        }
        if(yosef2==2){
            if(zeyad2(fakeboard,col)==0){
                printf("WON :D\n\n");
                exit(0);
            }
        }

        printf("\nBlack King is on Check!\n");


    }

    char option;
    printf("\nPLAYER [2] TURN.\t\t\t\tNumber of moves made: %d\n\nPlease select whether to:\n", counter2);
    printf("(A) Play.\t(B) Surrender.\t (C) Save.\t (D) Undo.\t (E) Redo.\n");
    printf("Type your selection here noting that only A, B, C, D or E are the accepted values: ");
    do
    {
        scanf(" %c", &option);
    }while(!(option == 'A' || option == 'B' || option == 'C' || option == 'D' || option == 'E'));
    if(option == 'A')
    {
            if(counter2==0) saveBlackmove(board,displayed_white,displayed_black,PLAYER_INDICATOR);
            chBoard(board,col,displayed_white,displayed_black,2);
            saveWhitemove(board,displayed_white,displayed_black,PLAYER_INDICATOR);
            movecount(2);
            player1options(board,col,displayed_white,displayed_black);
            return 0;
    }
    else if(option == 'B')
    {
        printf("\nPlayer [2] surrendered!\n");
        printf("\nPress any key to exit.");
        getch();
        exit(0);
    }
    else if(option == 'C')
    {
        save(board,displayed_white,displayed_black);
        player2options(board,col,displayed_white,displayed_black);
    }
    else if(option == 'D'){
            int w=0,b=0;
        if(counter2-1>0){
            counter2-=1;
            loadBlackmove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
        }
        else if(counter2==1){
            counter2-=1;
            loadBlackmove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
        }
        else
            printf("Error\n");
        player2options(board,col,displayed_white,displayed_black);

    }
    else if(option == 'E'){
            int w=0,b=0;
            counter2++;
            itoa(counter2,ch_b,10);
            FILE *fptr2;
            fptr2 = fopen(ch_b,"r");
            if(!(fptr2==NULL)){

            loadBlackmove(board,displayed_white,displayed_black);
            for(i=0;i<16;i++){
                if(islower(displayed_white[i])) w++;
                if(isupper(displayed_black[i])) b++;
                }
                move_w = w;
                move_b = b;
            printboard(board);
            printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
            }
            else{
                printf("ERROR\n");
                counter2--;
            }
            player2options(board,col,displayed_white,displayed_black);

    }


}

//------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------//

int main()
{
    // Initializing the board and pieces and printing it at the beginning of the program.

      char board[8][8]={
                    {'R','N','B','Q','K','B','N','R'},
                    {'P','P','P','P','P','P','P','P'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'p','p','p','p','p','p','p','p'},
                    {'r','n','b','q','k','b','n','r'},
                    };


    char col[8][8]={{'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'},
                    {'.','-','.','-','.','-','.','-'},
                    {'-','.','-','.','-','.','-','.'}};

    char displayed_white[16],displayed_black[16] ,trigger;
    int i,j=0;
    for(i=0;i<16;i++){
        displayed_white[i] = '.'; displayed_black[i] = '-';
    }

    printf("(N)ew or (L)oad\n(Only N, for new game, AND L ,to load a previously saved game, are allowed): ");
    do
    {
        scanf(" %c", &trigger);
    }   while(!(trigger == 'N' || trigger == 'L'));
    // Printing the board:
    if(trigger == 'N')
    {
        printboard(board);

         printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
            player1options(board,col,displayed_white,displayed_black);
    }
    else if(trigger == 'L')
    {
        load(board,displayed_white,displayed_black);
        PLAYER_INDICATOR-='0';
        printboard(board);
        printf("\nRemoved White Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_white[i]);

            printf("\nRemoved Black Pieces\n");
            for(int i=0;i<16;i++)
                printf("%c ", displayed_black[i]);

            printf("\n");
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if(board[i][j]=='k'){
                        pos_white_king[0][0]=i;
                        pos_white_king[0][1]=j;

                    }
                    if(board[i][j]=='K'){
                        pos_black_king[0][0]=i;
                        pos_black_king[0][1]=j;

                    }
                }
            }


    }
    if(PLAYER_INDICATOR==1){
        player1options(board,col,displayed_white,displayed_black);
    }
    else if(PLAYER_INDICATOR==2){
        player2options(board,col,displayed_white,displayed_black);
    }
}

