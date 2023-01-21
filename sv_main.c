#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Gia{
	float giamo;
	float giadong;
};

typedef struct BST
{
	char Id[3];
	struct Gia data[10];
	struct BST *left;
	struct BST *right;
}node;
 
node *create();
void insert(node *,node *);
void preorder(node *);


void InManHinh(node *);
int ChucNang2(node *root, char ID[]);
void ChucNang3(node *root);

node *root=NULL,*temp;

int N; // so luong ma co phieu
int count = 0; // so tt theo id
char ID[3];
float mo[10], dong[10];

void docFile(char macophieu[], int sohang)
{
	FILE *fi = fopen("data.txt","r");
	fscanf(fi,"%d", &N);
	//printf("%d\n",N);
	
	int i = 0;
	char id[3];
	float giamo, giadong;
	int stt = 0;
	char str[255];
	for(i = 0; i < sohang; i++)
	{
		fgets(str,255,fi);
	}
	while(i < N*10)
	{
		fscanf(fi, "%s%f%f",&id, &giamo, &giadong);
		if(strcmp(macophieu, id) == 0)
		{
			mo[stt] = giamo;
			dong[stt] = giadong;
			stt++;
		}
		i ++;
		//printf("%s\t%g\t%g\n",id,giamo,giadong);
	}
	
	fclose(fi);
}

void ReadFile()
{
	FILE *f = fopen("data.txt","r");
	fscanf(f,"%d",&N);
	int i;
	float x1,x2;
	for(i = 0; i <N; i++)
	{
		fscanf(f,"%s%f%f",&ID,&x1,&x2);
	//	printf("%s\t%f\t%f\n",ID,x1,x2);
		docFile(ID,i);
		temp = create(ID,mo,dong);
		if(root==NULL)
			root=temp;
		else
			insert(root,temp);
	}
	fclose(f);
}

void menu()
{
	printf("----------------------------- MENU -----------------------------\n");
	printf("1. Chuc nang 1\n");
	printf("2. Chuc nang 2\n");
	printf("3. Chuc nang 3\n");
	printf("4. Chuc nang 4\n");
	printf("5. Chuc nang 5\n");
	printf("----------------------------------------------------------------\n");
	printf("Lua chon: ");
	
}
int main()
{
	int doc = 0;
	int chon = 0;
	while(1)
	{
		menu();
		scanf("%d",&chon);
		switch(chon)
		{
			case 1:
				{
					if(doc == 1)
					{
						printf("Thong tin da duoc doc vao cay nhi phan\n");
						break;
					}
					ReadFile();
					printf("Ma\tTB\n");
					InManHinh(root);
					doc = 1;
					break;
				}
			case 2:
				{
					if(doc == 0)
					{
						printf("Thong tin chua duoc doc vao cay nhi phan\n");
						break;
					}
					printf("Nhap vao Ma co phieu: ");
					scanf("%s",&ID);
					int trave = ChucNang2(root,ID);
					if(trave == 0)
					{
						printf("Khong tim thay\n");
					}
					break;
				}
			case 3:
				{
					if(doc == 0)
					{
						printf("Thong tin chua duoc doc vao cay nhi phan\n");
						break;
					}
					printf("Thong tin nhung ma chung khoan co xu huong tang\n ");
					ChucNang3(root);
					break;
				}
			case 4:
				{
					if(doc == 0)
					{
						printf("Thong tin chua duoc doc vao cay nhi phan\n");
						break;
					}
					break;
				}
			case 5:
				{
					printf("Thong tin tac gia: Nguyen Huu Khai\nMSSV: 20200310\n");
					return 0;
				}
		}
	}
	
	//preorder(root);
	//InManHinh(root);
	
}


node *create(char id[],float mo[], float dong[])
{
	node *temp;
	//printf("nEnter data:");
	temp=(node*)malloc(sizeof(node));
	//scanf("%d",&temp->data);
	strcpy(temp->Id,id);
	int i;
	for(i = 0; i < 10; i++)
	{
		temp->data[i].giamo = mo[i];
		temp->data[i].giadong = dong[i];
	}
	temp->left=temp->right=NULL;
	return temp;
}


void insert(node *root,node *temp)
{
	
	if(strcmp(temp->Id,root->Id) < 0)
	{
		if(root->left!=NULL)
			insert(root->left,temp);
		else
			root->left=temp;
	}
	if(strcmp(temp->Id,root->Id) > 0)
	{
		if(root->right!=NULL)
			insert(root->right,temp);
		else
			root->right=temp;
	}
}
float trungbinh = 0;
void InManHinh(node *root)
{
	if(root!=NULL)
	{
		trungbinh = 0;
		int i;
		for(i = 0; i < 10; i++)
		{
			trungbinh += root->data[i].giadong - root->data[i].giamo;
		}
		trungbinh = trungbinh/10;
		printf("%s %.3f\n",root->Id, trungbinh);
		InManHinh(root->left);
		InManHinh(root->right);
	}
}
int ChucNang2(node *root, char ID[])
{
	if(root!=NULL)
	{
		//printf("%s\n",root->Id);
		if(strcmp(root->Id,ID) == 0)
		{
			int i;
			float caonhat = root->data[0].giadong;
			float thapnhat = root->data[0].giadong;
			for(i = 0; i < 10; i++)
			{
				if(root->data[i].giadong > caonhat)
				{
					caonhat = root->data[i].giadong;
				}
				
				if(root->data[i].giadong < thapnhat)
				{
					thapnhat = root->data[i].giadong;
				}
			}
			printf("Tim thay:\n");
			printf("%s: Gia dong cua cao nhat: %.3f, Gia dong cua thap nhat: %.3f\n",ID,caonhat,thapnhat);
			return 1;
		}
		ChucNang2(root->left, ID);
		ChucNang2(root->right, ID);
		
	}
	return 0;
}
void ChucNang3(node *root)
{
	if(root!=NULL)
	{
		if((root->data[0].giadong-root->data[0].giamo > 0) && (root->data[1].giadong-root->data[1].giamo > 0))
		{
			printf("%s\n",root->Id);
		}
		ChucNang3(root->left);
		ChucNang3(root->right);
	}
}
void preorder(node *root)
{
	if(root!=NULL)
	{
		printf("%s\n",root->Id);
		preorder(root->left);
		preorder(root->right);
	}
}
