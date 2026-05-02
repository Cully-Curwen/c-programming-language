#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void) {
        char s[MAXLINE];

        escape(s, "hello\tworld\n");
        printf("escape(\"hello\\tworld\\n\") = \"%s\"\n", s);

        escape(s, "\thello\n\tworld\n");
        printf("escape(\"\\thello\\n\\tworld\\n\") = \"%s\"\n", s);

        escape(s, "no escapes here");
        printf("escape(\"no escapes here\") = \"%s\"\n", s);

        escape(s, "");
        printf("escape(\"\") = \"%s\"\n", s);

        escape(s, "line1\nline2\nline3\n");
        printf("escape(\"line1\\nline2\\nline3\\n\") = \"%s\"\n", s);

        printf("\n--- unescape ---\n\n");

        unescape(s, "hello\\tworld\\n");
        printf("unescape(\"hello\\\\tworld\\\\n\") = \"%s\"\n", s);

        unescape(s, "\\thello\\n\\tworld\\n");
        printf("unescape(\"\\\\thello\\\\n\\\\tworld\\\\n\") = \"%s\"\n", s);

        unescape(s, "no escapes here");
        printf("unescape(\"no escapes here\") = \"%s\"\n", s);

        unescape(s, "");
        printf("unescape(\"\") = \"%s\"\n", s);

        return 0;
}

void escape(char s[], char t[]) {
        int i, j;

        for (i = j = 0; t[i] != '\0'; i++) {
                switch (t[i]) {
                case '\t':
                        s[j++] = '\\';
                        s[j++] = 't';
                        break;
                case '\n':
                        s[j++] = '\\';
                        s[j++] = 'n';
                        break;
                case '\\':
                        s[j++] = '\\';
                        s[j++] = '\\';
                        break;
                default:
                        s[j++] = t[i];
                        break;
                }
        }
        s[j] = '\0';
        return;
}

void unescape(char s[], char t[]) {
        int i, j;

        for (i = j = 0; t[i] != '\0'; i++) {
                if (t[i] == '\\')
                        switch (t[++i]) {
                        case 't':
                                s[j++] = '\t';
                                break;
                        case 'n':
                                s[j++] = '\n';
                                break;
                        case '\\':
                                s[j++] = '\\';
                                break;
                        default:
                                s[j++] = t[i];
                                break;
                        }
                else
                        s[j++] = t[i];
        }
        s[j] = '\0';
        return;
}



