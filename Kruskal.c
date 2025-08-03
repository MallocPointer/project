#include <stdio.h>
#include <stdlib.h>
#define N 50   //最大顶点数最大值设置大一点
#define M 200   //最大边数M设置大一点

//实际存在边和点的数目
int m, n;   //m为顶点数，n为边的数目

void initInfo() {
	scanf("%d%d", &m, &n);
}


//边结构体
typedef struct Edge {
	int vir0, vir1;
	int weight;
}Edge;

Edge edges[M];  // 存储所有边

//录入边的数据, 一次全部输入完毕
void initSide() {
	int vir0, vir1, weight;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &vir0, vir1, &weight);
		edges[i].vir0 = vir0;
		edges[i].vir1 = vir1;
		edges[i].weight = weight;
	}
}

//边排序 此排序算法应该能后期优化
//按照权值从小到大排序
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
//初始化并查集
void initVir(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = i;   //初始化时每个点都是自己的root
	}
}

//查找当前节点的root编号
int Find(int x) {
	if (parent[x] != x) {
		return Find(parent[x]);
	}
	else return x;
}

//合并两个集合
void union_set(int a, int b) {   //a, b 为两节点
	int rootA = Find(a);
	int rootB = Find(b);

	/*
	   1.rootA == rootB时 说明这是同一棵最小生成树树上的节点
	   所以不需要任何操作

	   2.rootA != rootB时 说明不是同一棵最小生成树
	   所以需要向后续操作标明: A树的root是B树
	   以此来让后面的判断保证不出环
	   wearning:这里我之前的疑惑是假设A和B之间甚至没有边连着，如何进行这个挂载
	      正确解释是: 原本就没有想着挂载，也不能挂载，此处标记的意义在于后续节
		              点要挂载的时候溯源时知道这两个节点逻辑上连接了，但实际不
					  连接，因为无实际边连接
		  现在还有的思考是如何做到最终实际通过其他方式合并这两颗树，但目前还能
		  继续写下去
	*/	
	if (rootA != rootB) {   
		parent[rootA] = rootB;
	}
}


//找到当前节点集合的root编号
int Find(int *parent, int f) {
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

//优先级数组
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