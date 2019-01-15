#include "BTree.h"

/**
 * ��B-��t���ҹؼ���key����r���أ�pt, i, tag��
 * �����ҳɹ�����tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���key
 * ����tag=0����Ҫ����ؼ���key��Ӧλ��pt����е�i-1�͵�i���ؼ���֮��
 *
 * @param t B-��
 * @param key �����ҵĹؼ���
 * @param r B-���Ĳ��ҽ������
 */
void SearchBTree(BTree t, KeyType key, Result &r) {
    int i = 0;
    int found = 0;
    BTree p = t; // һ��ʼָ�����㣬֮��ָ�������
    BTree q = NULL; // ָ��������˫��
    while (p != NULL && found == 0) {
        i = Search(p, key);
        if (i <= p->keynum && p->key[i] == key) {
            found = 1;
        } else {
            q = p;
            p = p->ptr[i - 1]; // ָ������
        }
    }
    if (1 == found) { // ���ҳɹ�������key��λ��p��i
        r.pt = p;
        r.i = i;
        r.tag = 1;
    } else { // ����ʧ�ܣ�����key�Ĳ���λ��q��i
        r.pt = q;
        r.i = i;
        r.tag = 0;
    }
}

/**
 * ��p->key[1 .. p->keynum]��key��������λ��
 *
 * @param p B-���Ľ��p
 * @param key �ؼ���
 * @return key��p����λ��
 */
int Search(BTree p, KeyType key) {
    int i = 1;
    while (i <= p->keynum && key > p->key[i]) {
        i++;
    }
    return i;
}

/**
 * ��B-��t��q����key[i - 1]��key[i]֮�����ؼ���key
 * ���������ؼ��ָ�������B-���Ľף�����˫��ָ�������н�����
 *
 * @param t B-��
 * @param key ������Ĺؼ���
 * @param q �ؼ��ֲ���Ľ��
 * @param i ����λ��
 */
void InsertBTree(BTree &t, KeyType key, BTree q, int i) {
    KeyType x;
    int s;
    int finished = FALSE;
    int needNewRoot = FALSE;
    BTree ap;
    if (NULL == q) {
        newRoot(t, NULL, key, NULL);
    } else {
        x = key;
        ap = NULL;
        while (FALSE == needNewRoot && FALSE == finished) {
            Insert(q, i, x, ap); // x��ap�ֱ���뵽q->key[i]��q->ptr[i]
            if (q->keynum < m) {
                finished = TRUE;
            } else {
                // ����q���
                s = (m + 1) / 2; // �õ��м���λ��
                split(q, s, ap);
                x = q->key[s];
                // ��˫��λ�ò���ؼ���x
                if (q->parent != NULL) {
                    q = q->parent;
                    i = Search(q, x); // Ѱ�Ҳ����λ��
                } else {
                    needNewRoot = TRUE;
                }
            }
        }
        if (TRUE == needNewRoot) {
            newRoot(t, q, x, ap);
        }
    }
}

/**
 * ��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������ap��ָ�½��
 *
 * @param q B-�����
 * @param s �м�λ��
 * @param ap �½�㣬�������ԭ���ĺ�һ��ؼ���
 */
void split(BTree &q, int s, BTree &ap) {
    int i, j;
    int n = q->keynum; // �ؼ�������
    ap = (BTree)malloc(sizeof(BTNode));
    ap->ptr[0] = q->ptr[s];
    for (i = s + 1, j = 1; i <= n; i++, j++) {
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
    }
    ap->keynum = n - s;
    ap->parent = q->parent;
    for (i = 0; i <= n - s; i++) {
        // �޸��½����ӽ���parent��
        if (ap->ptr[i] != NULL) {
            ap->ptr[i]->parent = ap;
        }
    }
    q->keynum = s - 1; // �޸�q���Ĺؼ�������
}

/**
 * �����µĸ����
 *
 * @param t B-��
 * @param p B-�����
 * @param key �ؼ���
 * @param ap B-�����
 */
void newRoot(BTree &t, BTree p, KeyType key, BTree ap) {
    t = (BTree)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = key;
    if (p != NULL) {
        p->parent = t;
    }
    if (ap != NULL) {
        ap->parent = t;
    }
    t->parent = NULL;
}

/**
 * �ؼ���key���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
 *
 * @param q ����Ŀ����
 * @param i ����λ��
 * @param key ������Ĺؼ���
 * @param ap �½��ָ��
 */
void Insert(BTree &q, int i, KeyType key, BTree ap) {
    int j;
    int n = q->keynum;
    for (j = n; j >= i; j--) {
        // ����
        q->key[j + 1] = q->key[j];
        q->ptr[j + 1] = q->ptr[j];
    }
    q->key[i] = key;
    q->ptr[i] = ap;
    if (ap != NULL) {
        ap->parent = q;
    }
    q->keynum++;
}

/**
 * ɾ��B-����p���ĵ�i���ؼ���
 *
 * @param t B-��
 * @param p Ŀ��ؼ������ڽ��
 * @param i �ؼ���λ��
 */
void DeleteBTree(BTree &t, BTree &p, int i) {
    if (p->ptr[i] != NULL) {
        // �������²���ն˽��
        Successor(p, i); // �ҵ�������²���ն˽�����С�ؼ��ִ�����
        DeleteBTree(t, p, 1); // ɾ�����²���ն˽���е���С�ؼ���
    } else {
        Remove(p, i); // �ӽ��p��ɾ��key[i]
        if (p->keynum < (m - 1) / 2) {
            Restore(t, p); // ����B��
        }
    }
}

/**
 * ��Ai�������ҳ����²���ն˽�����С�ؼ��ִ���Ki
 *
 * @param p B-�����
 * @param i �ؼ���λ��
 */
void Successor(BTree &p, int i) {
    BTree leaf = p;
    if (NULL == p) {
        return;
    }
    leaf = leaf->ptr[i]; // ָ������
    while (NULL != leaf->ptr[0]) {
        // �ҵ����²���ն˽��
        leaf = leaf->ptr[0];
    }
    p->key[i] = leaf->key[1];
    p = leaf;
}

/**
 * �ӽ��p�Ƴ��ؼ���key[i]
 *
 * @param p B-�����
 * @param i �ؼ���λ��
 */
void Remove(BTree &p, int i) {
    int k;
    // ָ����key��������
    for (k = i; k < p->keynum; k++) {
        p->key[k] = p->key[k + 1];
        p->ptr[k] = p->ptr[k + 1];
    }
    p->keynum--;
}

/**
 * ����B-��
 *
 * @param t B-��
 * @param p B-�����
 */
void Restore(BTree &t, BTree &p) {
    BTree parent, leftBrother, rightBrother; // ��ɾ���ĸ���㡢�����ֵ�
    parent = p->parent;
    if (parent != NULL) { // ����㲻Ϊ��
        // Ѱ�������ֵ�
        int i;
        for (i = 0; i <= parent->keynum; i++) {
            if (parent->ptr[i] == p) {
                break;
            }
        }
        if (i > 0) {
            leftBrother = parent->ptr[i - 1];
        } else {
            leftBrother = NULL;
        }
        if (i < parent->keynum) {
            rightBrother = parent->ptr[i + 1];
        } else {
            rightBrother = NULL;
        }

        // ���ֵܻ����ֵ��и���ؼ���
        if ((leftBrother != NULL && leftBrother->keynum >= (m + 1) / 2) ||
            (rightBrother != NULL && rightBrother->keynum >= (m + 1) / 2)) {
            BorrowFromBrother(p, leftBrother, rightBrother, parent, i);
        } else {
            // �����ֵܶ�û����ؼ��֣���Ҫ�ϲ�
            if (leftBrother != NULL) {
                MegerWithLeftBrother(leftBrother, parent, p, t, i); // �����ֵܺϲ�
            } else if (rightBrother != NULL) {
                MegerWithRightBrother(rightBrother, parent, p, t, i);
            } else  {
                //����������������ʱ�ı�����
                for (int j = 0; j <= p->keynum + 1; j++) {
                    if (p->ptr[j] != NULL) {
                        t = p->ptr[j];
                        break;
                    }
                }
                t->parent = NULL;
            }
        }
    } else {
        //���ڵ㣬ȥ�����ڵ㣬ʹ����һ��
        BTree a;
        for (int j = 0; j <= p->keynum + 1; j++) {
            if (p->ptr[j] != NULL) {
                a = p;
                p = p->ptr[j];
                a->ptr[j] = NULL;
                free(a);
                break;
            }
        }
        t = p;
        t->parent = NULL;
    }
}

/**
 * ���ֵܽ�ؼ���
 *
 * @param p B-�����
 * @param leftBrother p�������ֵܽ��
 * @param rightBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param i λ��
 */
void BorrowFromBrother(BTree &p, BTree &leftBrother, BTree &rightBrother, BTree &parent, int &i) {
    // ���ֵ��и���ؼ��֣������ֵܽ�
    if (leftBrother != NULL && leftBrother->keynum >= (m + 1) / 2) {
        for (int j = p->keynum + 1; j > 0; j--) {
            // �ؼ�����ָ����ƣ��ڳ���һ��λ��
            if (j > 1) {
                p->key[j] = p->key[j - 1];
            }
            p->ptr[j] = p->ptr[j - 1];
        }
        p->ptr[0] = leftBrother->ptr[leftBrother->keynum];
        if (p->ptr[0] != NULL) {
            p->ptr[0]->parent = p;
        }
        leftBrother->ptr[leftBrother->keynum] = NULL;
        p->key[1] = parent->key[i]; // ��ɾ���游���ؼ���
        parent->key[i] = leftBrother->key[leftBrother->keynum]; // ������key��Ϊ��ɾ������ֵܵ����ؼ���
        leftBrother->keynum--;
        p->keynum++;
    } else if (rightBrother != NULL && rightBrother->keynum >= (m + 1) / 2) { // ���ֵ��и���ؼ���
        p->key[p->keynum + 1] = parent->key[i + 1];
        p->ptr[p->keynum + 1] = rightBrother->ptr[0];    // ����ָ��ָ�����ֵ�����ߵ�����ָ��
        if (p->ptr[p->keynum + 1] != NULL) {
            p->ptr[p->keynum + 1]->parent = p;
        }
        p->keynum++;
        parent->key[i + 1] = rightBrother->key[1];        // ���������ֵܽ�ؼ���
        for (int j = 0; j < rightBrother->keynum; j++) {
            if (j > 0) {
                rightBrother->key[j] = rightBrother->key[j + 1];
            }
            rightBrother->ptr[j] = rightBrother->ptr[j + 1];
        }
        rightBrother->ptr[rightBrother->keynum] = NULL;
        rightBrother->keynum--;
    }
}

/**
 * �����ֵܺϲ�
 *
 * @param leftBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param p B-�����
 * @param t B-��
 * @param i λ��
 */
void MegerWithLeftBrother(BTree &leftBrother, BTree &parent, BTree &p, BTree &t, int &i) {
    // �����ֵܺϲ�
    leftBrother->key[leftBrother->keynum + 1] = parent->key[i];    // �Ӹ�������·ָ�ڵ������ֵܵĹؼ���
    leftBrother->ptr[leftBrother->keynum + 1] = p->ptr[0];
    if (leftBrother->ptr[leftBrother->keynum + 1] != NULL) {
        leftBrother->ptr[leftBrother->keynum + 1]->parent = leftBrother;    // �����ֵܵĽ�㣬���˽�����ʱ��Ҫ���丸��ָ��ָ������
    }
    leftBrother->keynum++; //���ֵܹؼ�����1
    for (int j = 1; j <= p->keynum; j++) {
        // �ѱ����Ĺؼ��ֺ�����ָ�븳�����ֵ�
        leftBrother->key[leftBrother->keynum + j] = p->key[j];
        leftBrother->ptr[leftBrother->keynum + j] = p->ptr[j];
        if (leftBrother->ptr[leftBrother->keynum + j] != NULL) {
            leftBrother->ptr[leftBrother->keynum + j]->parent = leftBrother;
        }
    }
    leftBrother->keynum += p->keynum;
    parent->ptr[i] = NULL;
    free(p);    // �ͷ�p���
    for (int j = i;j < parent->keynum; j++) {
        // ����
        parent->key[j] = parent->key[j + 1];
        parent->ptr[j] = parent->ptr[j + 1];
    }
    parent->ptr[parent->keynum] = NULL;
    parent->keynum--;        // �����ؼ��ָ�����1
    if (t == parent) {
        // �����ʱ�����Ϊ�����򵱸����û�йؼ���ʱ�ŵ���
        if (0 == parent->keynum) {
            for (int j = 0;j <= parent->keynum + 1; j++) {
                if (parent->ptr[j] != NULL) {
                    t = parent->ptr[j];
                    break;
                }
                t->parent = NULL;
            }
        }
    } else {
        // �������㲻Ϊ��������Ҫ�ж��Ƿ���Ҫ���µ���
        if (parent->keynum < (m - 1) / 2) {
            Restore(t, parent);
        }
    }
}
/**
 * �����ֵܺϲ�
 *
 * @param rightBrother p�������ֵܽ��
 * @param parent p���ĸ��׽��
 * @param p B-�����
 * @param t B-��
 * @param i λ��
 */
void MegerWithRightBrother(BTree &rightBrother, BTree &parent, BTree &p, BTree &t, int &i) {
    // �����ֵܺϲ�
    for (int j = (rightBrother->keynum); j > 0; j--) {
        if (j > 0) {
            rightBrother->key[j + 1 + p->keynum] = rightBrother->key[j];
        }
        rightBrother->ptr[j + 1 + p->keynum] = rightBrother->ptr[j];
    }
    rightBrother->key[p->keynum + 1] = parent->key[i + 1];    // �Ѹ����ķָ��������ֵܺ����ֵܵĹؼ���������ʹ��
    for (int j = 0; j <= p->keynum; j++) {
        // �ѱ����Ĺؼ��ּ�����ָ���ƶ����ֵ���ȥ
        if (j > 0) {
            rightBrother->key[j] = p->key[j];
        }
        rightBrother->ptr[j] = p->ptr[j];
        if (rightBrother->ptr[j] != NULL) {
            rightBrother->ptr[j]->parent = rightBrother;    // �����ֵܵĽ����Ҫ���丸���ָ�����ֵ�
        }
    }
    rightBrother->keynum += (p->keynum + 1);
    parent->ptr[i] = NULL;
    free(p); // �ͷ�p���
    for (int j = i;j < parent->keynum;j++) {
        if (j > i) {
            parent->key[j] = parent->key[j + 1];
        }
        parent->ptr[j] = parent->ptr[j + 1];
    }
    if (1 == parent->keynum) {
        // ���������ڹؼ��ּ���֮ǰֻ��һ����㣬��ô��Ҫ�Ѹ������Һ��Ӹ�ֵ������
        parent->ptr[0] = parent->ptr[1];
    }
    parent->ptr[parent->keynum] = NULL;
    parent->keynum--;                    // �����ؼ�������1
    if (t == parent) {
        //�����ʱ�����Ϊ�����򵱸����û�йؼ���ʱ�ŵ���
        if (0 == parent->keynum) {
            for (int j = 0; j <= parent->keynum + 1; j++) {
                if (parent->ptr[j] != NULL) {
                    t = parent->ptr[j];
                    break;
                }
            }
            t->parent = NULL;
        }
    } else {
        //�������㲻Ϊ��������Ҫ�ж��Ƿ���Ҫ���µ���
        if (parent->keynum < (m - 1) / 2) {
            Restore(t, parent);
        }
    }
}
/**
 * ���ؼ��ִ�С�������B-���ؼ���
 *
 * @param t B-��
 */
void OrderTraverseBTree(BTree t) {
    int i;
    if (NULL == t) {
        return;
    }
    for (i = 0; i <= t->keynum; i++) {
        if (i > 0) {
            printf("%d  ", t->key[i]);
        }
        if (t->ptr[i] != NULL) {
            OrderTraverseBTree(t->ptr[i]);
        }
    }
}

/**
 * �԰�������ʽ��ӡB��
 *
 * @param t B-��
 * @param x ������
 */
void PrintBTree(BTree t, int x) {
    if (!t) return;
	int  i;
	printf("\n");
	for (i = 0; i <= x; i++) putchar(' ');           // ����x  
	for (i = 1; i <= t->keynum; i++){                //�����ǰ�������йؼ���	
		printf("%d,", t->key[i]);
	}
	for (i = 0; i <= t->keynum; i++)              // �ݹ���ʾ�������ؼ���  
		PrintBTree(t->ptr[i], x + 7);
}

/**
 * B-���ؼ�������
 *
 * @param t B-��
 * @return ����B���ؼ���������Ϊ���򷵻�0
 */
int BTreeKeyNumber(BTree t) {
    int i;
    int keyNumber = 0;
    if (NULL == t) {
        return 0;
    }
    keyNumber += t->keynum;
    for (i = 0; i<= t->keynum; i++) {
        if (t->ptr[i] != NULL) {
            keyNumber += BTreeKeyNumber(t->ptr[i]);
        }
    }
    return keyNumber;
}

/**
 * ����B-��
 * @param t B-��
 */
void DestoryBTree(BTree &t) {
    if (NULL == t) {
        return;
    }
    for (int i = 0; i <= t->keynum; i++) {
        if (t->ptr[i] != NULL) {
            DestoryBTree(t->ptr[i]);
        }
    }
    free(t);
}

/**
 * ��ʼ��B��
 *
 * @param t B��
 */
void InitBTree(BTree &t) {
    t = NULL;
}


/**
 * ���������ָ����С��B��
 *
 * @param t B��
 * @param keyNumbe �ؼ�������
 */
void CreateBTreeRandom(BTree &t, int keyNumber) {
    KeyType key;
    Result r;
    srand((unsigned int) time(NULL));
    t = NULL;
    for (int i = 0; i < keyNumber; i++) {
        key = rand() % 100;
        SearchBTree(t, key, r);
        if (r.tag == 0) {
            InsertBTree(t, key, r.pt, r.i);
        }
    }
}

