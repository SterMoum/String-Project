#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

void ap(char *command, char ***words, char ***sentences, char ***paragraphs, int *wc, int *sc, int *pc);

void fw(char *command,char **words,int wc);

void fs(char *command,char **sentences,int sc);

void fp(char *command,char **paragraphs,int pc);

void owf(char **words,int wc,char ***pinax,int **counter,int *k);

void owl(char **words,int wc);

void bubbleSort(int **arr, int *n,char ***buffer,char a);

int main()
{
    char **words = NULL;
    char **sentences = NULL;
    char **paragraphs = NULL;
    int wc = 0, sc = 0, pc = 0;
    char **buffer=NULL;
    int *counter=NULL;
    int k=1;

    char *command = malloc(SIZE*sizeof(char));
    char run = 1,count_ap=0;

    while (run)
    {
        fgets(command, SIZE, stdin);
        if (command[strlen(command)-1] == '\n') command[strlen(command)-1] = '\0';
        fflush(stdin);

        if (command[0] == 'a' && command[1] == 'p' && command[2] == ':')
        {
            command += 3;
            ap(command, &words, &sentences, &paragraphs, &wc, &sc, &pc);
            count_ap++;

        }
        else if (command[0] == 'f' && command[1]=='w' && command[2]==':'){
            command += 3;
            fw(command,words,wc);
        }
        else if (command[0]=='f' && command[1]=='s' && command[2]==':'){
            command+=3;
            fs(command,sentences,sc);
        }

        else if (command[0] == 'f' && command[1]=='p' && command[2]==':'){
            command += 3;
            fp(command,paragraphs,pc);
        }
        else if(command[0]=='o' && command[1]=='w' && command[2]=='f')
        {

            if(count_ap==1){
               owf(words,wc,&buffer,&counter,&k);
                for(int i=0;i<k;i++)
                        printf("%s [%d]\n",buffer[i],counter[i]);
            }
            else{
                char done=1;

                char **temp=NULL;

                int *counter1=NULL;

                int k_temp=1;


                owf(words,wc,&temp,&counter1,&k_temp);

                for(int i=0; i<k; i++){
                    for(int j=0; j<k_temp && done; j++){
                        if(!strcmp(buffer[i],temp[j])){
                           done=0;
                           counter[i]+=counter1[j];
                           printf("counter1[%d]=%d",j,counter1[j]);
                           counter1[j]=0;
                           strcpy(temp[j],"");
                        }
                    }
                    done=1;
                }
                    int size=k;
                    for(int i=size; i < size + k_temp; i++){
                        for (int j=0; j<k_temp && done; j++){
                            if (counter1[j]){
                                k++;
                                buffer=realloc(buffer,k*sizeof(char*));
                                buffer[i]=malloc(strlen(temp[j])*sizeof(char));
                                strcpy(buffer[i],temp[j]);
                                counter[i]=malloc(k*sizeof(int));
                                counter[i]=counter1[j];
                                done=0;
                                counter1[j]=0;
                            }
                        }
                        done=1;
                    }
                    free(temp);
                    free(counter1);

    int temp1;
    char temp_string[20];


        for(int i=0;i<k-1;i++)
        {
            for (int j=0;j<k-i-1;j++)
            {
                    if (counter[j]<counter[j+1])
                {
                        temp1=counter[j];
                        counter[j]=counter[j+1];
                        counter[j+1]=temp1;
                        strcpy(temp_string,buffer[j]);
                        strcpy(buffer[j],buffer[j+1]);
                        strcpy(buffer[j+1],temp_string);

                }
                    else if(counter[j]==counter[j+1])
                    {
                        if (strcmp(buffer[j],buffer[j+1])>0)
                        {
                            strcpy(temp_string,buffer[j]);
                            strcpy(buffer[j],buffer[j+1]);
                            strcpy(buffer[j+1],temp_string);
                        }
                    }
            }
    }

                    for(int i=0;i<k;i++)
                        printf("%s [%d]\n",buffer[i],counter[i]);

                }
        }

        else if(command[0]=='o' && command[1]=='w' && command[2]=='l'){

            owl(words,wc);
        }

        else if (command[0]=='q' && command[1]=='t')
            run=0;
    }

    free(paragraphs);
    free(sentences);
    free(words);
    return 0;
}

void ap(char *command, char ***words, char ***sentences, char ***paragraphs, int *wc, int *sc, int *pc)
{
    char local_s[512];
    int lc = 0;



    paragraphs = realloc(*paragraphs, (*pc+1)*sizeof(char));
    *paragraphs[*pc] = calloc(SIZE, sizeof(char));

    strcpy(*paragraphs[*pc], command);
    (*pc)++;

    for (int i = 0; i < strlen(command); i++)
    {
        if (
            command[i] != '.' &&
            command[i] != '?' &&
            command[i] != '!' &&
            command[i] != ';'
            )
        {
            local_s[lc++] = command[i];
        }
        else if (
                 i > 0 &&
                 command[i-1] != '.' &&
                 command[i-1] != '?' &&
                 command[i-1] != '!' &&
                 command[i-1] != ';'
            )
        {
            sentences = realloc(*sentences, (*sc+1)*sizeof(char));
            (*sentences)[*sc] = calloc(SIZE, sizeof(char));
            local_s[lc] = '\0';
            strcpy((*sentences)[*sc],local_s);
            if ((*sentences)[*sc][0] == ' ') (*sentences)[*sc]++;
            lc = 0;
            (*sc)++;
        }
    }

    strcpy(local_s, "");
    lc = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (
            command[i] != '.' &&
            command[i] != '?' &&
            command[i] != '!' &&
            command[i] != ';' &&
            command[i] != ' ' &&
            command[i] != ','
            )
        {
            local_s[lc++] = command[i];
        }
        else if (
                 i > 0 &&
                 command[i-1] != '.' &&
                 command[i-1] != '?' &&
                 command[i-1] != '!' &&
                 command[i-1] != ';' &&
                 command[i-1] != ' ' &&
                 command[i-1] != ','
            )
        {
            words = realloc(*words, (*wc+1)*sizeof(char));
            (*words)[*wc] = calloc(SIZE, sizeof(char));
            local_s[lc] = '\0';
            strcpy((*words)[*wc],local_s);
            lc = 0;
            (*wc)++;
        }
    }
}
char contains(char arr[][100],char str[],int size)
{
    for(int i=0;i<size;i++){
        if(!strcmp(arr[i],str))
            return 1;
    }
    return 0;
}
void fw(char *command,char **words,int wc)
{
    char temp[wc][100];
    int k=0;
    for(int i=0; i<wc; i++)
    {
        if(strstr(words[i],command)!= NULL)
        {
            if(!contains(temp,words[i],wc)) {
                printf("%s\n",words[i]);
                strcpy(temp[k++],words[i]);
            }
        }
    }
}
void fs(char *command,char **sentences,int sc)
{
    char temp[sc][100];
    int k=0;
    for(int i=0; i<sc; i++)
    {
        if(strstr(sentences[i],command)!= NULL)
        {
            if(!contains(temp,sentences[i],sc)) {
                printf("%s\n",sentences[i]);
                strcpy(temp[k++],sentences[i]);
            }
        }
    }
}
void fp(char *command,char **paragraphs,int pc)
{
    char temp[pc][100];
    int k=0;
    for(int i=0; i<pc; i++)
    {
        if(strstr(paragraphs[i],command)!= NULL)
        {
            if(!contains(temp,paragraphs[i],pc)) {
                paragraphs[i][strlen(paragraphs[i])-1]='\0';
                printf("%s\n",paragraphs[i]);
                strcpy(temp[k++],paragraphs[i]);
            }
        }
    }
}
void bubbleSort(int **arr, int *n,char ***buffer,char a)
{
    int i,j,temp;

    char temp_string[20];
if(a){

        for(i=0;i<(*n)-1;i++)
        {
            for (j=0;j<(*n)-i-1;j++)
            {
                    if ((*arr)[j]<(*arr)[j+1])
                {
                        temp=(*arr)[j];
                        (*arr)[j]=(*arr)[j+1];
                        (*arr)[j+1]=temp;
                        strcpy(temp_string,(*buffer)[j]);
                        strcpy((*buffer)[j],(*buffer)[j+1]);
                        strcpy((*buffer)[j+1],temp_string);

                }
                    else if((*arr)[j]==(*arr)[j+1])
                    {
                        if (strcmp((*buffer)[j],(*buffer)[j+1])>0)
                        {
                            strcpy(temp_string,(*buffer)[j]);
                            strcpy((*buffer)[j],(*buffer)[j+1]);
                            strcpy((*buffer)[j+1],temp_string);
                        }
                    }
            }
    }
}
else {
         for(i=0;i<(*n)-1;i++)
        {
            for (j=0;j<(*n)-i-1;j++)
            {
                    if ((*arr)[j]>((*arr)[j+1]))
                {
                        temp=(*arr)[j];
                        (*arr)[j]=(*arr)[j+1];
                        (*arr)[j+1]=temp;
                        strcpy(temp_string,(*buffer)[j]);
                        strcpy((*buffer)[j],(*buffer)[j+1]);
                        strcpy((*buffer)[j+1],temp_string);

                }
                    else if((*arr)[j]==(*arr)[j+1])
                    {
                        if (strcmp((*buffer)[j],(*buffer)[j+1])>0)
                        {
                            strcpy(temp_string,(*buffer)[j]);
                            strcpy((*buffer)[j],(*buffer)[j+1]);
                            strcpy((*buffer)[j+1],temp_string);
                        }
                    }
            }
        }

    }
}

void owf(char **words,int wc,char ***pinax,int **counter,int *k)
{
    char flag=1;
    (pinax)=realloc((*pinax),(*k)*sizeof(char));

    (*pinax)[0]=malloc(strlen(words[0])*sizeof(char));
    strcpy((*pinax)[0],words[0]);

    for(int i=1; i<wc; i++){
        for(int j=0;j<(*k) && flag;j++){
            if(!strcmp((*pinax)[j],words[i])){
                flag=0;
            }
        }
        if(flag){
             (pinax)=realloc((*pinax),((*k)+1)*sizeof(char));
             (*pinax)[*k]=malloc(strlen(words[i])*sizeof(char));
             strcpy((*pinax)[*k],words[i]);
             (*k)++;
        }
        else
            flag=1;
    }
    *counter=realloc(*counter,(*k)*sizeof(int));
    for(int i=0; i<(*k); i++)
        (*counter)[i]=0;

    for(int i=0; i<(*k); i++){
        for(int j=0; j<wc; j++){
            if(!strcmp((*pinax)[i],words[j]))
                (*counter)[i]++;
        }
    }
    int temp;

    char temp_string[20];


        for(int i=0;i<(*k)-1;i++)
        {
            for (int j=0;j<(*k)-i-1;j++)
            {
                    if ((*counter)[j]<(*counter)[j+1])
                {
                        temp=(*counter)[j];
                        (*counter)[j]=(*counter)[j+1];
                        (*counter)[j+1]=temp;
                        strcpy(temp_string,(*pinax)[j]);
                        strcpy((*pinax)[j],(*pinax)[j+1]);
                        strcpy((*pinax)[j+1],temp_string);

                }
                    else if((*counter)[j]==(*counter)[j+1])
                    {
                        if (strcmp((*pinax)[j],(*pinax)[j+1])>0)
                        {
                            strcpy(temp_string,(*pinax)[j]);
                            strcpy((*pinax)[j],(*pinax)[j+1]);
                            strcpy((*pinax)[j+1],temp_string);
                        }
                    }
            }
    }
}

void owl(char **words,int wc)
{
    int k=1;
    char flag=1;
    char **buffer;
    buffer=malloc(k*sizeof(char*));

    buffer[0]=malloc(strlen(words[0])*sizeof(char));
    strcpy(buffer[0],words[0]);

    for(int i=1; i<wc; i++){
        for(int j=0;j<k && flag;j++){
            if(!strcmp(buffer[j],words[i])){
                flag=0;
            }
        }
        if(flag){
             buffer=realloc(buffer,(k+1)*sizeof(char*));
             buffer[k]=malloc(strlen(words[i])*sizeof(char));
             strcpy(buffer[k],words[i]);
             k++;
        }
        else
            flag=1;
    }
    int Len_words[k];
    for (int i=0; i<k; i++)
        Len_words[i]=strlen(buffer[i]);
   // bubbleSort(Len_words,k,&buffer,0);
    for(int i=0; i<k; i++)
        printf("%s [%d]\n",buffer[i],Len_words[i]);
    free(buffer);
}