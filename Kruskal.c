#include <stdio.h>
#include <stdlib.h>
#define N 50   //��󶥵������ֵ���ô�һ��
#define M 200   //������M���ô�һ��

//ʵ�ʴ��ڱߺ͵����Ŀ
int m, n;   //mΪ��������nΪ�ߵ���Ŀ

void initInfo() {
	scanf_s("%d%d", &m, &n);
}


//�߽ṹ��
typedef struct Edge {
	int vir0, vir1;
	int weight;
}Edge;

Edge edges[M];  // �洢���б�

//¼��ߵ�����, һ��ȫ���������
void initSide() {
	int vir0, vir1, weight;
	for (int i = 0; i < n; i++) {
		scanf_s("%d%d%d", &vir0, &vir1, &weight);
		edges[i].vir0 = vir0;
		edges[i].vir1 = vir1;
		edges[i].weight = weight;
	}
}

//������ �������㷨Ӧ���ܺ����Ż�
//����Ȩֵ��С��������
void sort() {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (edges[j].weight > edges[j + 1].weight) {
				Edge temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
}


//==============================================

int parent[N];
//��ʼ�����鼯
void initVir(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = i;   //��ʼ��ʱÿ���㶼���Լ���root
	}
}

//�����Ч�ʱ��·���ѭ��Ч�ʸ�
//���ҵ�ǰ�ڵ��root��� ·��ѹ��
int Find(int x) {
	if (parent[x] != x) {
		parent[x] = Find(parent[x]);
	}
	return parent[x];
}

/*
//�ҵ���ǰ�ڵ㼯�ϵ�root���
int Find(int f) {
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}
*/

//�ϲ���������
void union_set(int a, int b) {   //a, b Ϊ���ڵ�
	int rootA = Find(a);
	int rootB = Find(b);

	/*
	   1.rootA == rootBʱ ˵������ͬһ����С���������ϵĽڵ�
	   ���Բ���Ҫ�κβ���

	   2.rootA != rootBʱ ˵������ͬһ����С������
	   ������Ҫ�������������: A����root��B��
	   �Դ����ú�����жϱ�֤������
	   wearning:������֮ǰ���ɻ��Ǽ���A��B֮������û�б����ţ���ν����������
	      ��ȷ������: ԭ����û�����Ź��أ�Ҳ���ܹ��أ��˴���ǵ��������ں�����
		              ��Ҫ���ص�ʱ����Դʱ֪���������ڵ��߼��������ˣ���ʵ�ʲ�
					  ���ӣ���Ϊ��ʵ�ʱ�����
		  ���ڻ��е�˼���������������ʵ��ͨ��������ʽ�ϲ�������������Ŀǰ����
		  ����д��ȥ
	*/	
	if (rootA != rootB) {   
		parent[rootA] = rootB;
	}
}





int kruskal() {
	//�ṩ��������
	initInfo();

	//��ʼ�����鼯
	initVir(m);

	//��������
	initSide();

	//���������
	sort();

	int res = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		int u = edges[i].vir0;
		int v = edges[i].vir1;
		int w = edges[i].weight;
		int fu = Find(u), fv = Find(v);
		if (fu != fv) {
			union_set(u, v);  // ���������Ϻϲ�
			res += w;         // ���ϱ�Ȩ
			cnt++;            // ������1

			printf("ѡ�бߣ�%d �� %d��Ȩֵ = %d\n", u, v, w);

			if (cnt == m - 1) break;  // ��������������
		}
	}
	return res;


}

int main() {
	int ans = kruskal();
	printf("��С������Ȩֵ��: %d\n", ans);
	getchar();
	getchar();
	return 0;
}
