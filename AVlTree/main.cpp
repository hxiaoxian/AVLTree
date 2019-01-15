#include <iostream>
#include "main.h"
#include "AVLTree.h"

using namespace std;

int flag = NOT_CREATED; //ȫ�ֱ���

void AVLMenu() {
    system("color 03");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************ƽ���������ʾ����ѡ��˵�************************\n");
    printf("*                                                                        *\n");
    printf("****************  17�����繤��2��  �����ƣ�3117005073�� ******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. ����һ��ƽ�������                          *\n");
    printf("*                         2. ������                                    *\n");
    printf("*                         3. ɾ�����                                    *\n");
    printf("*                         4. ���ҽ��                                    *\n");
    printf("*                         5. ����ƽ�������                              *\n");
    printf("*                         6. ��ʾƽ�������                              *\n");
    printf("*                         7. ����һ��ƽ�������                          *\n");
    printf("*                         8. �ϲ�����ƽ�������                          *\n");
    printf("*                         9. ����ƽ�������                              *\n");
    printf("*                         0. �˳�                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}


void InitBBSTreeOperation(BBSTree &T) {
    if (flag == HAVE_BEEN_CREATED) {
        printf("ƽ���������֮ǰ�Ѿ��������벻Ҫ�ظ���������\n");
        return;
    }
    printf("\nƽ������鴴���ɹ�����ʼΪ����\n");
    flag = HAVE_BEEN_CREATED;
}

/**
 * ���������
 *
 * @param T ƽ�������
 */
void InsertAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("ƽ���������δ����������ڵ�ʧ��\n");
        return;
    } else {
        if (NULL == T) {
            printf("��ƽ�������Ϊ�գ��������\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\nƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
        }
        while (1) {
            printf("�����������Ĺؼ���: ");
            KeyType key;
            RcdType rcd;
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                printf("��������ȷ��ֵ\n");
                printf("������Ҫ������Ĺؼ���: ");
            }
            rcd.key = key;
            Status taller = FALSE;
            if (SearchBBST(T, key) != NULL) {
                printf("����ʧ�ܣ��ý���Ѵ���\n\n");
            } else {
                InsertAVL(T, rcd, taller);
                printf("\n----------------------------------------------------");
                printf("\n������ƽ�������Ϊ��");
                ParenthesisPrintBBST(T);
                printf("\n��ʾ���£�\n\n");
                ConcaveTablePrintBBST(T,1);
                printf("\n----------------------------------------------------\n\n");
            }
            printf("�Ƿ�������룿��Y/y����, ���������Ϊ�񣩣�");
            char c;
            getchar();
            scanf("%c", &c);
            fflush(stdin);
            if (toupper(c) != 'Y') {
                break;
            }
            printf("\n");
        }
    }
}

/**
 * ɾ��������
 *
 * @param T ƽ�������
 */
void DeleteAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("ƽ���������δ������ɾ���ڵ�ʧ��\n");
    } else {
        if (NULL == T) {
            printf("ƽ�������Ϊ�գ�ɾ���ڵ�ʧ��\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\nƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("������Ҫɾ�����Ĺؼ���: ");
                KeyType key;
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    printf("��������ȷ��ֵ\n");
                    printf("������Ҫɾ�����Ĺؼ���: ");
                }
                if (NULL == SearchBBST(T, key)) {
                    printf("�ý�㲻����\n\n");
                } else {
                    Status shorter = FALSE;
                    DeleteAVL(T, key, shorter);
                    if (NULL == T) {
                        printf("ƽ��������Ѿ�Ϊ�գ����ü���ɾ��\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
                        printf("\nɾ�����ƽ�������Ϊ��");
                        ParenthesisPrintBBST(T);
                        printf("\n�������ʾ���£�\n\n");
                        ConcaveTablePrintBBST(T,1);
                        printf("\n----------------------------------------------------\n\n");
                    }
                }
                printf("�Ƿ����ɾ������Y/y����, ���������Ϊ�񣩣�");
                char c;
                getchar();
                scanf("%c", &c);
                fflush(stdin);
                if (toupper(c) != 'Y') {
                    break;
                }
                printf("\n");
            }
        }
    }
}

/**
 * ���ҽ�����
 *
 * @param T ƽ�������
 */
void SearchBBSTOperation(BBSTree &T) {
    KeyType key;
    BBSTree p;
    if (NOT_CREATED == flag) {
        printf("ƽ���������δ���������ҽڵ�ʧ��\n");
        return;
    } 
    if (NULL == T) {
        printf("ƽ�������Ϊ��\n");
        return;
    } else {
        printf("\n----------------------------------------------------");
        printf("\nƽ�������Ϊ��");
        ParenthesisPrintBBST(T);
        printf("\n��ʾ���£�\n\n");
        ConcaveTablePrintBBST(T,1);
        printf("\n----------------------------------------------------\n\n");
        printf("��������Ҫ���ҵĹؼ��֣�");
        while (scanf("%d", &key) != 1) {
            printf("��������ȷ��ֵ\n");
            printf("��������ҽ��Ĺؼ��֣�");
        }
        p = SearchBBST(T, key);
        if (NULL == p) {
            printf("��ѯʧ�ܣ��ý�㲻����\n");
        } else {
            printf("�Թؼ������ڽ����������£�\n");
            printf("------------------------------------------------------\n");
            ParenthesisPrintBBST(p);
            printf("\n\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(p,1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void VisitOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("ƽ�������δ����\n");
    } else {
        if (NULL == T) {
            printf("ƽ�������Ϊ��\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\nƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n\nǰ��������Ϊ��");
            PreOrderTraverse(T, visit);
            printf("\n����������Ϊ��");
            InOrderTraverse(T, visit);
            printf("\n����������Ϊ��");
            PostOrderTraverse(T, visit);
            printf("\n��α������Ϊ��");
            PrintNodeByLevel(T);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ��ӡƽ�����������
 *
 * @param T ƽ�������
 */
void PrintBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        printf("ƽ�������δ����\n");
    } else {
        if (NULL == T) {
            printf("ƽ�������Ϊ��\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\nƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void SpiltBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        printf("ƽ�������δ����\n");
    } else {
        if (NULL == T) {
            printf("ƽ�������Ϊ�գ����Ѳ���ʧ��\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\nƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
            printf("������Ҫ���ѵĹؼ���: ");
            KeyType key;
            while (1) {
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    printf("��������ȷ��ֵ\n");
                    printf("������Ҫ���ѵĹؼ���: ");

                }
                if (NULL == SearchBBST(T, key)) {
                    printf("�ùؼ��ֲ���ƽ��������С�\n\n");
                    printf("����������Ҫ���ѵĹؼ���: ");
                } else {
                    BBSTree T1 = NULL;
                    BBSTree T2 = NULL;
                    SpiltBBST(T, key, T1, T2);
                    printf("\n----------------------------------------------------\n");
                    printf("��һ������Ϊ��", key);
                    ParenthesisPrintBBST(T1);
                    printf("\n��ʾ���£�\n\n");
                    ConcaveTablePrintBBST(T1,1);
                    printf("\n----------------------------------------------------\n\n");

                    printf("\n----------------------------------------------------\n");
                    printf("�ڶ�������Ϊ��", key);
                    ParenthesisPrintBBST(T2);
                    printf("\n��ʾ���£�\n\n");
                    ConcaveTablePrintBBST(T2,1);
                    printf("\n----------------------------------------------------\n\n");
                    break;
                }
            }
        }
    }
}

/**
 * �ϲ�ƽ�����������
 *
 * @param T ƽ�������
 */
void MergeBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("ƽ�������δ����\n");
    } else {
        if (NULL == T) {
            printf("ԭƽ�������Ϊ�գ����ڴ���һ��ƽ��������ϲ����˶�������\n");
        } else {
            printf("\n--------------------------------------- -------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n��ʾ���£�\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------");
            printf("\n���ڴ���һ��ƽ��������ϲ����˶�������\n\n");
        }
        BBSTree T1 = NULL;
        InsertAVLOperation(T1); 
        printf("\n----------------------------------------------------");
        printf("\n��ƽ�������Ϊ��");
        ParenthesisPrintBBST(T1);
        printf("\n��ʾ���£�\n\n");
        ConcaveTablePrintBBST(T1,1);
        printf("\n----------------------------------------------------\n\n");
        MergeBBST(T, T1);
        DestroyBBST(T1);
        printf("\n----------------------------------------------------");
        printf("\n�ϲ���ƽ�������Ϊ��");
        ParenthesisPrintBBST(T);
        printf("\n��ʾ���£�\n\n");
        ConcaveTablePrintBBST(T,1);
        printf("\n----------------------------------------------------\n\n");
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void DestroyBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("ƽ�������δ����������ʧ��\n");
    } else if (flag == HAVE_BEEN_CREATED){
        if (NULL == T) {
            printf("ƽ�������Ϊ�գ���������\n");
        } else {
            printf("�Ƿ�����ƽ�����������Y/y����, ���������Ϊ��");
            char option;
			option = getchar();
			fflush(stdin); 
			if(option == 'Y' || option == 'y'){
			 DestroyBBST(T);
             flag = NOT_CREATED;
			}
        }
    }
}
 
/**
 * ����������
 */
int main()
{
    system("color 03");
    int num; 
    BBSTree T;
    while (1) {
        AVLMenu();
        printf("�����������");
        scanf("%d", &num);
        getchar();
        fflush(stdin);
        if (0 == num) {
            printf("\n�Ƿ��˳�����Y/y����, ���������Ϊ��");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (flag == HAVE_BEEN_CREATED) {
                    DestroyBBST(T);
                }
                exit(-1);
            }
        } else {
            switch (num) {
                case 1: InitBBSTreeOperation(T); break; 
                case 2: InsertAVLOperation(T); break; 
                case 3: DeleteAVLOperation(T); break; 
                case 4: SearchBBSTOperation(T); break; 
                case 5: VisitOperation(T); break;
                case 6: PrintBBSTOperation(T); break; 
                case 7: SpiltBBSTOperation(T); break;
                case 8: MergeBBSTOperation(T); break; 
                case 9: DestroyBBSTOperation(T); break; 
                default: printf("��������ȷ��ֵ\n"); break;
            }
        }
        system("PAUSE");
        system("CLS"); // ��������
    }
    system("PAUSE");
    getch();
    return 0;
}
