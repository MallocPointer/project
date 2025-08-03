#include <stdio.h>
#include <stdlib.h>
#define N 50   //��󶥵������ֵ���ô�һ��
#define M 200   //������M���ô�һ��

//ʵ�ʴ��ڱߺ͵����Ŀ
int m, n;   //mΪ��������nΪ�ߵ���Ŀ

void initInfo() {
	scanf("%d%d", &m, &n);
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
		scanf("%d%d%d", &vir0, vir1, &weight);
		edges[i].vir0 = vir0;
		edges[i].vir1 = vir1;
		edges[i].weight = weight;
	}
}

//������ �������㷨Ӧ���ܺ����Ż�
//����Ȩֵ��С��������
void sort() {
	for (int j = 0; j < n; j++) {
		for (int k = j; k < n - j - 1; k++) {
			if (edges[k].weight > edges[k + 1].weight) {
				int temp = edges[k].weight;
				edges[k].weight = edges[k + 1].weight;
				edges[k + 1].weight = temp;
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

//���ҵ�ǰ�ڵ��root���
int Find(int x) {
	if (parent[x] != x) {
		return Find(parent[x]);
	}
	else return x;
}

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


//�ҵ���ǰ�ڵ㼯�ϵ�root���
int Find(int *parent, int f) {
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

//���ȼ�����
void priorityArrary(Edge pri[]) {
	int j = 0, k = 0;
	while ((pri + j) != NULL) {
		while ((pri + j + k + 1) != NULL) {
			if ((pri + j + k)->weight > (pri + j + k + 1)->weight) {
				Edge temp;
				temp = *(pri + j + k);
				*(pri + j + k) = *(pri + j + k + 1);
				*(pri + j + k + 1) = temp;
			}
			k++;
		}
		j++;
	}
}