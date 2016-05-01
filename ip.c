#include <stdio.h>
/*
 * License:
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
 * Author: Osanda Malith Jayathissa 
 * Website: http://osandamalith.wordpress.com
 */
void banner() {
  fflush(stdin);
  const static char *banner = 
"\t\t\t---------------------------------\n"
"\t\t\t    Welcome to IP Obfuscator     \n"
"\t\t\t     Coded by @OsandaMalith		\n"
"\t\t\thttp://osandamalith.wordpress.com\n"
"\t\t\t---------------------------------\n";
  for(banner; *banner; ++banner) fprintf(stdout, "%c", *banner);            
}

int isValidIp(char *str) {
    int segs = 0;    
    int chcnt = 0;   
    int accum = 0;   

    if (!str) return 0;

    while (*str) {
        if (*str == '.') {
            if (!chcnt) return 0;
            if (++segs == 4) return 0;
            chcnt = accum = 0;
            str++;
            continue;
        }
        if ((*str < '0') || (*str > '9')) return 0;
        if ((accum = accum * 10 + *str - '0') > 255) return 0;
        chcnt++;
        str++;
    }
    if (segs != 3) return 0;
    if (!chcnt) return 0;
    return 1;
}

int main(){
	banner();
	int i;
	unsigned int final;
	char ip[100], *token;
	unsigned int dec[3];
	const char deli[2] = ".";

	printf("\n[+] Enter your IP: ");
	fgets(ip, sizeof(ip), stdin);
	strtok(ip, "\n");
	
	if(!isValidIp(ip)) {
		fprintf(stderr,"%s","[!] Enter a valid ip");
		exit(-1);
	}
	token = strtok(ip, deli);
	
	for(i=0; token; i++){
		*(dec+i) = atoi(token);
		token = strtok(NULL, deli);
	}
	
	final = (*dec << 24)|(*(dec+1) << 16)|(*(dec+2) << 8)|*(dec+3);

	printf("\n[~] Obfuscated IP is http://%u", final);
}
