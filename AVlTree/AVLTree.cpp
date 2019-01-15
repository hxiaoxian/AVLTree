#include "main.h"
#include "AVLTree.h"

/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void R_Rotate(BBSTree &p) {
    BBSTree lc = p->lchild;  // lcָ��p��������
    p->lchild = lc->rchild;  // lc������������Ϊp����������
    lc->rchild = p;          // ��p���Ϊlc�����Һ���
    p = lc;                  // pָ���µĸ����
}

/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void L_Rotate(BBSTree &p) {   
    BBSTree rc = p->rchild;  //rcָ��p�����Һ��� 
    p->rchild = rc->lchild;  //rc������������Ϊp���������� 
    rc->lchild = p;          //��p���Ϊrc�������� 
    p = rc;                  //pָ���µĸ���� 
}

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void LeftBalance(BBSTree &T) {
    BBSTree lc, rd;
    lc = T->lchild;
    switch (lc->bf) {
        case LH:                   //LL�ͣ��������������������ȸ� 
            T->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        case RH:                   //LR�ͣ���˫������         
            rd = lc->rchild;  
            switch (rd->bf) {      //�޸�T�������ӵ�ƽ������ 
                case LH: {
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                } case EH: {
                    T->bf = lc->bf = EH;
                    break;
                } case RH: {
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                }
            }
            rd->bf = EH;
            L_Rotate(T->lchild);    //��T������������������ 
            R_Rotate(T);            //��T���������� 
            break;
    }
}

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void RightBalance(BBSTree &T) {
    BBSTree rc, ld;
    rc = T->rchild;
    switch (rc->bf) {
        case RH:                  //RR�ͣ��Ҹ���������������ȸ� 
            T->bf = rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:                  //RL�ͣ���˫������ 
            ld = rc->lchild;
            switch (ld->bf) {     //�޸�T�����Һ��ӵ�ƽ������ 
                case RH:
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case LH:
                    T->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH;
            R_Rotate(T->rchild);    //��T������������������
            L_Rotate(T);            //��T���������� 
            break;
    }
}

/**
 * ƽ��������Ĳ������
 *
 * @param T ƽ�������T
 * @param e ������Ԫ��
 * @param taller �߶��Ƿ��� 
 * @return �ɹ�����TRUE
 */
Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
    if (NULL == T) {
        // TΪ�գ�������
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    } else if (e.key == T->data.key) {
        // �Ѿ����ڸõ㣬����ʧ�� 
        taller = FALSE;
        return FALSE;
    } else if (e.key < T->data.key) {
        // ���뵽������
        if (FALSE == InsertAVL(T->lchild, e, taller)) {
            return FALSE;   //δ���� 
        }
        if (TRUE == taller) {
            switch (T->bf) {  //���T��ƽ������ 
                case LH: {    //ԭ��ߣ���ƽ�⴦�� 
                    LeftBalance(T);
                    taller = FALSE;
                    break;
                } case EH: {  //ԭ�ȸߣ����� 
                    T->bf = LH;
                    taller = TRUE;
                    break;
                } case RH: {  //ԭ�Ҹߣ���ȸ� 
                    T->bf = EH; 
                    taller = FALSE;
                    break;
                }
            }
        }
    } else {         //���뵽�������� 
        if (FALSE == InsertAVL(T->rchild, e, taller)) {
            return FALSE;
        }
        if (TRUE == taller) {
            switch (T->bf) {   //���ƽ������ 
                case LH: {     //ԭ��ߣ���ȸ� 
                    T->bf = EH;
                    taller = FALSE;
                    break;
                } case EH: {   //ԭ�ȸߣ����Ҹ� 
                    T->bf = RH;
                    taller = TRUE;
                    break;
                } case RH: {   //ԭ�Ҹߣ���ƽ�⴦�� 
                    RightBalance(T);
                    taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * ��AVL������key
 *
 * @param T AVL��
 * @param key �����ҵĹؼ���
 * @return �ҵ��򷵻ظùؼ��ֵĽ�㣬�Ҳ����򷵻�NULL
 */
BBSTree SearchBBST(BBSTree T, KeyType key) {
    if (NULL == T) {
        return NULL;
    }
    if (T->data.key == key) {     
        return T;
    }
    if (T->data.key > key) {
        return SearchBBST(T->lchild, key);  //�������ݹ���� 
    }
    return SearchBBST(T->rchild, key);      //�������ݹ���� 
}

/**
 *���ű�ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ParenthesisPrintBBST(BBSTree T) {
    if (NULL == T) {
        return;
	}
    printf("%d", T->data.key);
    if (T->lchild != NULL || T->rchild != NULL) {
        printf("(");
        if (T->lchild != NULL) {
            ParenthesisPrintBBST(T->lchild);
        } else if (T->rchild != NULL) {
            printf("#");
        }
        printf(",");
        if (T->rchild != NULL) {
            ParenthesisPrintBBST(T->rchild);
        } else if (T->lchild != NULL){
            printf("#");
        }
        printf(")");
    }
}

/**
 * ��ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ConcaveTablePrintBBST(BBSTree T,int level){
	if(T == NULL)  return;
	int i ;
	if(T->rchild) 
	ConcaveTablePrintBBST(T->rchild,level + 1);
    for(i = 0;i < level;i++)
        printf("     ");//��ӡi���ո��Ա�ʾ�����
    printf("%d\n",T->data);
    if(T->lchild)  
	ConcaveTablePrintBBST(T->lchild,level + 1);
} 
/*
void ConcaveTablePrintBBST(BBSTree T){
	if(T != NULL){
		ConcaveTablePrintBBST(T->lchild);
		for(int i = 0;i < TreeDepth(T); i++){
		printf("\t"); 
	}
	printf("%5d\n",T->data);
	ConcaveTablePrintBBST(T->rchild);
   }
} */ 
/**
 * ��ƽ������������ 
 *
 * @param T AVL��
 */
int TreeDepth(BBSTree T){
     int rightdep,leftdep;
    if(T == NULL)
        return 0;
    if(T->lchild != NULL)
        leftdep = TreeDepth(T->lchild);   //����������� 
    else
        leftdep = 0;
    if(T->rchild != NULL)
        rightdep = TreeDepth(T->rchild);  //����������� 
    else
        rightdep = 0;
    return (rightdep > leftdep) ? rightdep + 1 : leftdep + 1;
}



/**
 * ƽ���������ɾ������
 *
 * @param T
 * @param key
 * @param shorter
 * @return
 */
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter) {
    if (NULL == T) {
        // ��Ϊ��
        return FALSE;
    } else if (T->data.key == key) {
        // �ҵ�Ԫ�ؽ��
        BBSTree p = NULL;
        if (NULL == T->lchild) {
            // ������Ϊ��
            p = T;
            T = T->rchild;
            free(p);
            shorter = TRUE; // �߶ȱ䰫
        } else if (T->rchild == NULL) {
            // ������Ϊ��
            p = T;
            T = T->lchild;
            free(p);
            shorter = TRUE; // �߶ȱ䰫
        } else {
            // ��������������
            p = T->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            T->data = p->data;
            // ����������ɾ��ǰ�����
            DeleteAVL(T->lchild, p->data.key, shorter);
        }
    } else if (T->data.key > key) {  //Ҫɾ���Ľ��Ԫ��ֵС�ڵ�ǰ�����Tֵ�����������н���ɾ�� 
        if (DeleteAVL(T->lchild, key, shorter) == FALSE) {
            return FALSE;  //�ݹ���ã�����������ʵʩɾ�� 
        }
        if (shorter == TRUE) {  //���ʱ����Ҫ�жϵ�ǰ������Ƿ���Ȼ����ƽ������ 
            switch (T->bf) {
                case LH: {      //ԭ��ߣ���ȸߣ����䰫 
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                } case EH: {    //ԭ�ȸߣ����Ҹ� 
                    T->bf = RH;
                    shorter = FALSE;
                    break;
                } case RH: {   
                    RightBalance(T); //ԭ�Ҹߣ��������ƽ�⴦�� 
                    if (T->rchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                }
            }
        }
    } else {    //Ҫɾ���Ľ��Ԫ��ֵ���ڵ�ǰ�����Tֵ�����������н���ɾ��
        if (DeleteAVL(T->rchild, key, shorter) == FALSE) {
            return FALSE; //�ݹ���ã�����������ʵʩɾ�� 
        }
        if (shorter == TRUE) {//���ʱ����Ҫ�жϵ�ǰ������Ƿ���Ȼ����ƽ������
            switch (T->bf) {
                case LH: {     //ԭ��ߣ��������ƽ�⴦�� 
                    LeftBalance(T);
                    if (T->lchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                } case EH: { //ԭ�ȸߣ������
                    T->bf = LH;
                    shorter = FALSE;
                    break;
                } case RH: { //ԭ�Ҹߣ���ȸߣ����䰫
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * ���ƽ��������ؼ���
 * @param key �ؼ���
 */
void visit(KeyType key) {
    printf("%d  ", key);
}

/**
 * ǰ�����ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PreOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
  	visit(T->data.key);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void InOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
    InOrderTraverse(T->lchild, visit);
    visit(T->data.key);
    InOrderTraverse(T->rchild, visit);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PostOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
      	return;
    }
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T->data.key);
}

/**
 * ��α���ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 * @param level ���
 * @return
 */
Status LevelOrderTraverse(BBSTree T, void( *visit)(KeyType), int level) {
    if (!T || level < 0) {
        return ERROR;
    }
    if (level == 0) {
        visit(T->data.key);
        return OK;
    }
    return LevelOrderTraverse(T->lchild, visit, level - 1) +
    		LevelOrderTraverse(T->rchild, visit, level - 1);
}


/**
 * �����ӡ
 *
 * @param T ƽ�������
 */
void PrintNodeByLevel(BBSTree T) {
    if (NULL == T) {
        return;
    }
    int level;
    for (level = 0; ; level++) {
        if (!LevelOrderTraverse(T, visit, level)) {
            break;
        }
    }
}

/**
 * ����ƽ����������ֳɴ���key��С��key������
 *
 * @param T �����ѵ�ƽ�������
 * @param key ���ѵĹؼ���
 * @param T1 �ؼ���ȫ��С��key��ƽ�������
 * @param T2 �ؼ���ȫ������key��ƽ�������
 */
void SpiltBBST(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
	if (T != NULL) {
		SpiltBBST(T->lchild, key, T1, T2); // �ݹ����������
		if(T->data.key > key) {
            InsertAVL(T1, T->data, taller);
		} else {
            InsertAVL(T2, T->data, taller);
		}
		SpiltBBST(T->rchild, key, T1, T2); // �ݹ���������� 
	}
}

/**
 * �ϲ�ƽ�������
 *
 * @param T1 �ϲ����ƽ�������
 * @param T2 ���ϲ���ƽ�������
 */
void MergeBBST(BBSTree &T1, BBSTree T2) {
    Status taller = FALSE;
    if (T2 != NULL) {
        MergeBBST(T1, T2->lchild);
        InsertAVL(T1, T2->data, taller);
        MergeBBST(T1, T2->rchild);
    }
}

/**
 * ����ƽ�������
 *
 * @param T ƽ�������
 */
void DestroyBBST(BBSTree &T) {
    if (T != NULL) {
        DestroyBBST(T->lchild);
        DestroyBBST(T->rchild);
        free(T);
    }
}


