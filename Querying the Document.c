#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// here is what you will code

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, char k) {
   return document[k - 1];
}

char**** get_document(char* text) {
    // intialize your variables
    int c=0,w=0,s=0,p=0,d=0 ;
    // allocate memory for document
    char**** document = (char****) malloc(sizeof(char***));
    document[0] = (char***) malloc(sizeof(char**));
    document[0] [0] = (char**) malloc(sizeof(char*));
    document[0] [0] [0] = (char*) malloc(sizeof(char));
    // initialize your document
    while (*text)   // if no char it will break loop
    {
        if (*text == ' '){
            // here is anew word
            c=0 ;
            w++;
            // here increase one adress in sentence
            document[p] [s] = realloc(document[p] [s] , sizeof(char*)*(w+1) );  
            // here allocate a memory for new address of word
            document[p] [s][w] = (char*) malloc(sizeof(char));
        }
        else if (*(text+1) == '\0'){
            // here is the end of the document >> for more save 
            break;
        }
        else if (*(text+1) == '\n'){
            c=0 ;
            w = 0;
            s=0;
            p++;
            // here increase one adress in document
            document  = realloc(document  , sizeof(char***)*(p+1) );
            // here allocate a memory for new address which should have anew address for paragraph ,sentenance and word
            document [p] = (char***) malloc(sizeof(char**));
            document[p] [s]= (char**) malloc(sizeof(char*));
            document[p] [s][w] = (char*) malloc(sizeof(char));
            text++;
        }
        else if (*text == '.'){
            c=0 ;
            w = 0;
            s++;
            // here increase one adress in paragraph
            document[p]  = realloc(document[p]  , sizeof(char**)*(s+1) );
            // here allocate a memory for new address which should have anew address for sentenance and word
            document[p] [s]= (char**) malloc(sizeof(char*));
            document[p] [s][w] = (char*) malloc(sizeof(char));
        }

        else{
            // here is a character
            c++;
            // here increase one adress in word which point to char
            document[p] [s] [w] = realloc(document[p] [s] [w], sizeof(char)*(c+1) );
            document[p] [s] [w][c-1] = *text;
            /* secret line of code */
            document[p][s][w][c] = '\0';
            /*        ****************           */

        }
        text++ ;
    }
    return document;
}
/* end of what you will need in code */

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}