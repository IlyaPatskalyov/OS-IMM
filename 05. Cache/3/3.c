#define MAX 1000
int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
int main(){
	int sum, i, j, y;
	for(y = 0; y < 200; y++)
	for(i = 0; i < MAX; i++)
		for(j = 0; j < MAX; j++)
			c[i][j] = a[i][j]*b[j][i];
}