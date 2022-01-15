#include<iostream>
#include<math.h>
using namespace std;
#define csize 20//��Ⱥ�Ĺ�ģ
#define c1 1.5
#define c2 1.5//ѧϰ����
#define dim 2//ά��
#define v_max 1
#define v_min -1//������Ⱥ���ٶȼ�ֵ
#define stri_max 10
#define stri_min -10//���弫��Сֵ
#define max_try 100
#define w 1//�������� 1

double pop_home[csize][dim];//������Ⱥ�Ĵ�С
double pop_v[csize][dim];//��Ⱥ������ٶ�
double pop_value[csize];//�����Ⱥ����Ӧ��
double best_fitnum[max_try];//���ÿ�ε�������Ӧֵ
double all_best_pos[dim];//��¼Ⱥ�弫ֵ��λ��
double all_best_num;//��¼Ⱥ�弫ֵ��Ӧ��ֵ
double pop_best_num[csize];//��¼�������Ӧ�ȼ�ֵ
double pop_best_pos[csize][dim];//��¼������Ӧ�ȼ�ֵ��λ��
double gen_best[max_try][dim];//��¼ÿһ���ļ�ֵλ��
double result[max_try];//��¼ÿһ������ֵ
double func(double x, double y) 
{
	
	return -((x * x) - (y * y));//��Ӧ�Ⱥ���

}



void init() //�����ʼ����Ⱥ����
{
	for (int i = 0; i < csize; i++) {
		for (int j = 0; j < dim; j++) {
			pop_home[i][j] = (((double)rand()) / RAND_MAX - 0.5) * 20;
			pop_v[i][j]= (((double)rand()) / RAND_MAX - 0.5) * 2;
			pop_value[i] = func(pop_home[i][j], pop_v[i][j]);
		}
		
	}//��ɳ�ʼ�����Լ���Ӧ��ֵ�ĳ�ʼָ��









}
double* find_max(double* fit,int size) //�ҵ���Ӧ�ȼ�ֵ���Լ�����Ӧ��λ��
{
	int num = 0;
	double max = *fit;
	double best[2];
	for (int i = 1; i < size; i++) {
		if (*(fit + i) > max) {
			num = i;
			max = *(fit + i);
		}
	}
	best[0] =num;
	best[1] = max;
	return best;
}


void PSO()//����Ⱥ�㷨��ֵ
{
	init();//
	double* bestfit = find_max(pop_value, csize);//�ҵ���Ⱥ�����λ��
	int index = int(*bestfit);//��¼Ⱥ�弫ֵ�ı��
	for (int i = 0; i < dim; i++) {
		all_best_pos[i] = pop_home[index][i];//��¼Ⱥ�弫ֵ�ĸ�ά�ȵ������¼����
	}
	all_best_num = (*bestfit + 1);//����Ⱥ�弫ֵ�Ĵ�С





	for (int i = 0; i < csize; i++) {
		pop_best_num[i] = pop_value[i];//��¼����ﵽ����ֵ
		for (int j = 0; j < dim; j++) {
			pop_best_pos[i][j] = pop_home[i][j];//��¼����ﵽ��ֵ������
		}
	}
	for (int i = 0; i < max_try; i++) 
	{
		for (int j = 0; j < csize; j++) {
			//���Ƚ��и�����ٶ��Լ�λ�ø���
			for (int k = 0; k < dim; k++)
			{
				double rand1 = (double)rand() / RAND_MAX; 
				double rand2 = (double)rand() / RAND_MAX;
				pop_v[j][k] = w * pop_v[j][k] + c1 * rand1 * (pop_best_pos[j][k] - pop_home[j][k]) + c2 * rand2 * (all_best_pos[k] - pop_home[j][k]);
				if (pop_v[j][k] > v_max)pop_v[j][k] = v_max;
				if (pop_v[j][k] < v_min)pop_v[j][k] = v_min;
				//λ�ø���
				pop_home[j][k] += pop_v[j][k];
				if (pop_home[j][k] > stri_max)pop_home[j][k] =stri_max;
				if (pop_home[j][k] <stri_min)pop_home[j][k] = stri_min;
			}
           
			pop_value[j] = func(pop_home[j][0], pop_home[j][1]);

			//���и��弫ֵ�ĸ���
			if (pop_value[j] > pop_best_num[j]) {
				for (int j2 = 0; j2 < dim; j2++) {
					pop_best_pos[j][j2] = pop_home[j][j2];

				}
				pop_best_num[j] = pop_value[j];
			}
			if (pop_value[j] > all_best_num) 
			{
				for (int j2 = 0; j2 < dim; j2++) {
					all_best_pos[j2] = pop_home[j][j2];
				}
				all_best_num = pop_value[j];
			}
			



		}
		for (int k1 = 0; k1 < dim; k1++) 
		{
			gen_best[i][k1] = all_best_pos[k1];
		}
		result[i] = all_best_num;
		cout << endl;
		cout << "��" << i << "�ε�����ֵΪ" << -all_best_num << endl;
		cout << "ȡ�ü�ֵ������Ϊ" << all_best_pos[0] << "  " << all_best_pos[1] << endl;

	}

}
int main() {
	PSO();//���м�����ֵ
	return 0;





}