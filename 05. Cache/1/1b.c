#define MAX 10000
int a[MAX][MAX];
int main(){
	int sum, i, j;
	for(i = 0; i < MAX; i++)
		for(j = 0; j < MAX; j++)
			sum += a[j][i];
}