/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "main.h"

#define  m  3             // B���Ľ�
#define NOT_INIT 0        // û�г�ʼ��
#define HAVE_BEEN_INIT 1  // �Ѿ���ʼ��

typedef int KeyType;      // �ؼ�������Ϊ��������

typedef struct {
  KeyType  key;
  char     data;
} Record;

typedef struct BTNode {
  int             keynum;        // ����йؼ��ָ����������Ĵ�С
  struct BTNode  *parent;        // ָ��˫�׽��
  KeyType         key[m+1];      // �ؼ���������0�ŵ�Ԫδ��
  struct BTNode  *ptr[m+1];      // ����ָ������
  Record         *recptr[m+1];   // ��¼ָ��������0�ŵ�Ԫδ��
} BTNode, *BTree;                // B������B��������

typedef struct {
  BTree    pt;      // ָ���ҵ��Ľ��
  int      i;       // 1..m���ڽ���еĹؼ������
  int      tag;     // 1:���ҳɹ���0:����ʧ��
} Result;           // ��B���Ĳ��ҽ������


/**
 * ��B-��t���ҹؼ���key����r���أ�pt, i, tag��
 * �����ҳɹ�����tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���key
 * ����tag=0����Ҫ����ؼ���key��Ӧλ��pt����е�i-1�͵�i���ؼ���֮��
 *
 * @param t B-��
 * @param key �����ҵĹؼ���
 * @param r B-���Ĳ��ҽ������
 */
void SearchBTree(BTree t, KeyType key, Result &r);

/**
 * ��p->key[1 .. p->keynum]��key��������λ��
 *
 * @param p B-���Ľ��p
 * @param key �ؼ���
 * @return key��p����λ��
 */
int Search(BTree p, KeyType key);

/**
 * ��B-��t��q����key[i - 1]��key[i]֮�����ؼ���key
 * ���������ؼ��ָ�������B-���Ľף�����˫��ָ�������н�����
 *
 * @param t B-��
 * @param key ������Ĺؼ���
 * @param q �ؼ��ֲ���Ľ��
 * @param i ����λ��
 */
void InsertBTree(BTree &t, KeyType key, BTree q, int i);

/**
 * ��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������ap��ָ�½��
 *
 * @param q B-�����
 * @param s �м�λ��
 * @param ap �½�㣬�������ԭ���ĺ�һ��ؼ���
 */
void split(BTree &q, int s, BTree &ap);

/**
 * �����µĸ����
 *
 * @param t B-��
 * @param p B-�����
 * @param key �ؼ���
 * @param ap B-�����
 */
void newRoot(BTree &t, BTree p, KeyType key, BTree ap);

/**
 * �ؼ���key���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
 *
 * @param q ����Ŀ����
 * @param i ����λ��
 * @param key ������Ĺؼ���
 * @param ap �½��ָ��
 */
void Insert(BTree &q, int i, KeyType key, BTree ap);

/**
 * ɾ��B-����p���ĵ�i���ؼ���
 *
 * @param t B-��
 * @param p Ŀ��ؼ������ڽ��
 * @param i �ؼ���λ��
 */
void DeleteBTree(BTree &t, BTree &p, int i);

/**
 * ��Ai�������ҳ����²���ն˽�����С�ؼ��ִ���Ki
 *
 * @param p B-�����
 * @param i �ؼ���λ��
 */
void Successor(BTree &p, int i);

/**
 * �ӽ��p�Ƴ��ؼ���key[i]
 *
 * @param p B-�����
 * @param i �ؼ���λ��
 */
void Remove(BTree &p, int i);

/**
 * ����B-��
 *
 * @param t B-��
 * @param p B-�����
 */
void Restore(BTree &t, BTree &p);

/**
 * ���ֵܽ�ؼ���
 *
 * @param p B-�����
 * @param leftBrother p�������ֵܽ��
 * @param rightBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param i λ��
 */
void BorrowFromBrother(BTree &p, BTree &leftBrother, BTree &rightBrother, BTree &parent, int &i);

/**
 * �����ֵܺϲ�
 *
 * @param leftBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param p B-�����
 * @param t B-��
 * @param i λ��
 */
void MegerWithLeftBrother(BTree &leftBrother, BTree &parent, BTree &p, BTree &t, int &i);

/**
 * �����ֵܺϲ�
 *
 * @param rightBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param p B-�����
 * @param t B-��
 * @param i λ��
 */
void MegerWithRightBrother(BTree &rightBrother, BTree &parent, BTree &p, BTree &t, int &i);

/**
 * ���ؼ��ִ�С�������B-���ؼ���
 *
 * @param t B-��
 */
void OrderTraverseBTree(BTree t);

/**
 * �԰�������ʽ��ӡB��
 *
 * @param t B-��
 * @param tab ������
 */
void PrintBTree(BTree t, int tab);

/**
 * B-���ؼ�������
 *
 * @param t B-��
 * @return ����B���ؼ���������Ϊ���򷵻�0
 */
int BTreeKeyNumber(BTree t);

/**
 * ����B-��
 * @param t B-��
 */
void DestoryBTree(BTree &t);

/**
 * ��ʼ��B��
 *
 * @param t B��
 */
void InitBTree(BTree &t);

/**
 * ���������ָ����С��B��
 *
 * @param t B��
 * @param keyNumbe �ؼ�������
 */
void CreateBTreeRandom(BTree &t, int keyNumber);
 

#endif 

