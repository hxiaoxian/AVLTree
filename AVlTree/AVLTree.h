#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED


#include "main.h"

#define LH        +1     // ����������������
#define EH         0     // ���������ȸ�
#define RH        -1     // ����������������
#define HAVE_BEEN_CREATED 1    // ƽ��������Ѿ�����
#define NOT_CREATED -1         // ƽ�������δ����


typedef int KeyType;    // �ؼ�������Ϊ��������

typedef struct {
    KeyType key;   // �ؼ�����
} RecordType, RcdType;    // ��¼����

typedef struct BBSTNode {
    RcdType data;
    int bf;         // ���ƽ������
    struct BBSTNode *lchild, *rchild;  // ���Һ���
} * BBSTree;  // ƽ�������


/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void R_Rotate(BBSTree &p);

/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void L_Rotate(BBSTree &p);

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void LeftBalance(BBSTree &T);

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void RightBalance(BBSTree &T);

/**
 * ƽ��������Ĳ������
 *
 * @param T ƽ�������T
 * @param e ������Ԫ��
 * @param taller �߶��Ƿ���
 * @return �ɹ�����TRUE
 */
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);

/**
 * ��AVL������key
 *
 * @param T AVL��
 * @param key �����ҵĹؼ���
 * @return �ҵ��򷵻ظùؼ��ֵĽ�㣬�Ҳ����򷵻�NULL
 */
BBSTree SearchBBST(BBSTree T, KeyType key);

/**
 * ������ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ConcaveTablePrintBBST(BBSTree T,int level);


int TreeDepth(BBSTree T);
/**
 * ���ű�ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ParenthesisPrintBBST(BBSTree T);

/**
 * ƽ���������ɾ������
 *
 * @param T
 * @param key
 * @param shorter
 * @return
 */
Status DeleteAVL(BBSTree &T, KeyType key, Status &lower);

/**
 * ���ƽ��������ؼ���
 * @param key �ؼ���
 */
void visit(KeyType key);

/**
 * ǰ�����ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PreOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void InOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PostOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * ��α���ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 * @param level ���
 * @return
 */
Status LevelOrderTraverse(BBSTree T, void( *visit)(KeyType), int level);

/**
 * �����ӡ
 *
 * @param T ƽ�������
 */
void PrintNodeByLevel(BBSTree T);

/**
 * ����ƽ����������ֳɴ���key��С��key������
 *
 * @param T �����ѵ�ƽ�������
 * @param key ���ѵĹؼ���
 * @param T1 �ؼ���ȫ��С��key��ƽ�������
 * @param T2 �ؼ���ȫ������key��ƽ�������
 */
void SpiltBBST(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);

/**
 * �ϲ�ƽ�������
 *
 * @param T1 �ϲ����ƽ�������
 * @param T2 ���ϲ���ƽ�������
 */
void MergeBBST(BBSTree &T1, BBSTree T2);

/**
 * ����ƽ�������
 *
 * @param T ƽ�������
 */
void DestroyBBST(BBSTree &T);

#endif 
