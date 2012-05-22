#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _memory_block
{
	struct _memory_block *pNext;
	struct _memory_block *pPrev;
	char *data;
}MemoryBlock

typedef struct _memory_pool
{
	unsigned int blockCount;
	unsigned int blockCountStep;
	unsigned int blockSize;
	unsigned int freeCount;
	MemoryBlcok *freeHead;
	MemoryBlock *freeTail;
	MemoryBlock *usedHead;
	MemoryBlock *usedTail;
	char *pBlockMemoryHead;
	char *pDataMemoryHead;
}Memorypool;

int Xpool_ini(unsigned int blockCount, unsigned int blockSize);
int Xpool_destory(void);
void *Xpool_alloc(unsigned int size);
int Xpool_free(void *ptr);

static int Xpool_block(unsigned int blockCount, unsigend int blockSize);
static MemoryPool memory;

int Xpool_init(unsigned int blockCount, unsigned int blockSize)
{
	Memorypool *p = &memory;
	p->blockCount = blcokCount;
	p->blockSize = blockSize;
	p->freeCount = blockCount;
	p->blockCountStep = 100;
	p->freeHead = p->freeTail = NULL;
	p->usedHead = p->usedTail = NULL;
	
	
	Xpool_block(blockCount, blockSize);  /*����鲢��������Ŀ����ӵ����п����*/
	return 0;
}

static int Xpool_block(unsigned int blockCount, unsigned int blockSize)
{
	Mempool *p = &memory;
	
	MemoryBlock *pPree = NULL;
	
	p->pBlockMemoryHead = (char *)malloc(sizeof(MemoryBlock) *blockCount);
	
	p->pDataMemoryHead = (char *)malloc((blockSize + sizeof(MemoryBlock *)) * blockCount);//����һ����������ڴ�ռ��Ź��û�ʹ�õĿռ�
	
	
	for (unsigned int i = 0; i<blockCount; i++)
	{
		pFree = (MemoryBlock *)(p->pBlockMemoryHead + (sizeof(MemoryBlock * i));
		pFree->data = p->pDataMemoryHead + ((blockSize + sizeof(MemoryBlock *))*i);
		pFree->pNext = NULL;
		pFree->pPrev = p->freeTail;
		
		if(p->freeHead == NULL)
		{
			p->freeHead = p->freeTail = pFree;
		}else{
			p->freeTail->pNext = pFree;
			p->freeTail = pFree;
		}
	}
		return 0;
}

int Xpool_destroy(void)
{
MemoryPool *p = &memory;
 
//�ͷ��ڴ����ռ���ڴ�
free(p->pBlockMemoryHead);
 
//�ͷ�����������ռ���ڴ�
free(p->pDataMemoryHead);
 
return 0;
}
 
//�����ڴ�
void* Xpool_alloc(unsigned int size)
{
MemoryPool *p = &memory;
MemoryBlock *block = NULL;
 
if(p->freeHead == NULL){//û�п��ÿռ�
Xpool_block(p->blockCountStep, p->blockSize);
}
 
block = p->freeHead;//��ȡ��ͷ�ڴ��
p->freeHead = block->pNext;//�����п������ͷ
p->freeCount--;//���п�������һ
block->pNext = NULL;
block->pPrev = p->usedTail;//�������ϸ�������ʹ�ÿ�����һ����
 
//��һ��ʹ���ڴ棿
if(p->usedHead == NULL){
p->usedHead = p->usedTail = block;//������ʹ�õ�ͷ��β��ָ�������
}else{//���ǵ�һ��
p->usedTail->pNext = block;
p->usedTail = block;
}
//����data��һ��ָ��Ŀռ䣬���ڱ��������ݹ����Ŀ��ַ
 
block->data = (char *)block;
return (char *)block->data + sizeof(MemoryBlock *);
}
 
//�����ڴ�
int Xpool_free(void *ptr)
{
MemoryPool *p = &memory;
char *realptr = (char *)ptr - sizeof(MemoryBlock *); //���ݿ���ʵ����ʼ��ַ
MemoryBlock *block = (MemoryBlock *)realptr;
 
if(block == NULL){
return NULL;
}
 
if(block->pPrev == NULL){//�����ͷ
p->usedHead = block->pNext;
if(p->usedHead != NULL){
p->usedHead->pPrev = NULL;
}
}else if(block->pNext == NULL){//�����β
p->usedTail = block->pPrev;
if(p->usedTail != NULL){
p->usedTail->pNext = NULL;
}
}else{//�м��
block->pPrev->pNext = block->pNext;
block->pNext->pPrev = block->pPrev;
}
 
//���ò���
block->pPrev = p->freeTail;
block->pNext = NULL;
block->data = realptr;
 
//�ӵ����п�����
p->freeTail->pNext = block;
p->freeTail = block;
p->freeCount++;
 
return 0;
}
 
int main(int argc, char *argv[])
{
Xpool_init(10, 96);
char *p = (char *)Xpool_alloc(20);
Xpool_free(p);
Xpool_destroy();
return 0;
}