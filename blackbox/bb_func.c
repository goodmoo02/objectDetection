#define size 256

void get_time(int num){
        time_t rawtime;
        struct tm *timeinfo;
	char* buffer = malloc(sizeof(char)*256);
        timeinfo = localtime(&rawtime);
	if (num == 1){		
        	strftime(buffer, size, "%Y%m%d_%H", timeinfo);
	else
		strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
	return buffer;
}

void makedir(char* pos){
	char addr[size] = {0};
	getcwd(addr, size);
	char* time_buf = get_time(1);
	
	
