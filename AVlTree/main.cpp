#include <iostream>
#include "main.h"
#include "AVLTree.h"

using namespace std;

int flag = NOT_CREATED; //全局变量

void AVLMenu() {
    system("color 03");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************平衡二叉树演示功能选择菜单************************\n");
    printf("*                                                                        *\n");
    printf("****************  17级网络工程2班  黄贤淦（3117005073） ******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. 创建一棵平衡二叉树                          *\n");
    printf("*                         2. 插入结点                                    *\n");
    printf("*                         3. 删除结点                                    *\n");
    printf("*                         4. 查找结点                                    *\n");
    printf("*                         5. 遍历平衡二叉树                              *\n");
    printf("*                         6. 显示平衡二叉树                              *\n");
    printf("*                         7. 分裂一棵平衡二叉树                          *\n");
    printf("*                         8. 合并两棵平衡二叉树                          *\n");
    printf("*                         9. 销毁平衡二叉树                              *\n");
    printf("*                         0. 退出                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}


void InitBBSTreeOperation(BBSTree &T) {
    if (flag == HAVE_BEEN_CREATED) {
        printf("平衡二叉树在之前已经创建，请不要重复创建操作\n");
        return;
    }
    printf("\n平衡二叉书创建成功，初始为空树\n");
    flag = HAVE_BEEN_CREATED;
}

/**
 * 插入结点操作
 *
 * @param T 平衡二叉树
 */
void InsertAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树还未创建，插入节点失败\n");
        return;
    } else {
        if (NULL == T) {
            printf("新平衡二叉树为空，请插入结点\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
        }
        while (1) {
            printf("请输入插入结点的关键字: ");
            KeyType key;
            RcdType rcd;
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                printf("请输入正确的值\n");
                printf("请输入要插入结点的关键字: ");
            }
            rcd.key = key;
            Status taller = FALSE;
            if (SearchBBST(T, key) != NULL) {
                printf("插入失败，该结点已存在\n\n");
            } else {
                InsertAVL(T, rcd, taller);
                printf("\n----------------------------------------------------");
                printf("\n插入后的平衡二叉树为：");
                ParenthesisPrintBBST(T);
                printf("\n显示如下：\n\n");
                ConcaveTablePrintBBST(T,1);
                printf("\n----------------------------------------------------\n\n");
            }
            printf("是否继续插入？（Y/y：是, 其他任意键为否）：");
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
 * 删除结点操作
 *
 * @param T 平衡二叉树
 */
void DeleteAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树还未创建，删除节点失败\n");
    } else {
        if (NULL == T) {
            printf("平衡二叉树为空，删除节点失败\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("请输入要删除结点的关键字: ");
                KeyType key;
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    printf("请输入正确的值\n");
                    printf("请输入要删除结点的关键字: ");
                }
                if (NULL == SearchBBST(T, key)) {
                    printf("该结点不存在\n\n");
                } else {
                    Status shorter = FALSE;
                    DeleteAVL(T, key, shorter);
                    if (NULL == T) {
                        printf("平衡二叉树已经为空，不用继续删除\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
                        printf("\n删除后的平衡二叉树为：");
                        ParenthesisPrintBBST(T);
                        printf("\n凹入表显示如下：\n\n");
                        ConcaveTablePrintBBST(T,1);
                        printf("\n----------------------------------------------------\n\n");
                    }
                }
                printf("是否继续删除？（Y/y：是, 其他任意键为否）：");
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
 * 查找结点操作
 *
 * @param T 平衡二叉树
 */
void SearchBBSTOperation(BBSTree &T) {
    KeyType key;
    BBSTree p;
    if (NOT_CREATED == flag) {
        printf("平衡二叉树还未创建，查找节点失败\n");
        return;
    } 
    if (NULL == T) {
        printf("平衡二叉树为空\n");
        return;
    } else {
        printf("\n----------------------------------------------------");
        printf("\n平衡二叉树为：");
        ParenthesisPrintBBST(T);
        printf("\n显示如下：\n\n");
        ConcaveTablePrintBBST(T,1);
        printf("\n----------------------------------------------------\n\n");
        printf("请输入您要查找的关键字：");
        while (scanf("%d", &key) != 1) {
            printf("请输入正确的值\n");
            printf("请输入查找结点的关键字：");
        }
        p = SearchBBST(T, key);
        if (NULL == p) {
            printf("查询失败，该结点不存在\n");
        } else {
            printf("以关键字所在结点的子树如下：\n");
            printf("------------------------------------------------------\n");
            ParenthesisPrintBBST(p);
            printf("\n\n显示如下：\n\n");
            ConcaveTablePrintBBST(p,1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 遍历平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void VisitOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("平衡二叉树未创建\n");
    } else {
        if (NULL == T) {
            printf("平衡二叉树为空\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n\n前序遍历输出为：");
            PreOrderTraverse(T, visit);
            printf("\n中序遍历输出为：");
            InOrderTraverse(T, visit);
            printf("\n后序遍历输出为：");
            PostOrderTraverse(T, visit);
            printf("\n层次遍历输出为：");
            PrintNodeByLevel(T);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 打印平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void PrintBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树未创建\n");
    } else {
        if (NULL == T) {
            printf("平衡二叉树为空\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 分裂平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void SpiltBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树未创建\n");
    } else {
        if (NULL == T) {
            printf("平衡二叉树为空，分裂操作失败\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------\n\n");
            printf("请输入要分裂的关键字: ");
            KeyType key;
            while (1) {
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    printf("请输入正确的值\n");
                    printf("请输入要分裂的关键字: ");

                }
                if (NULL == SearchBBST(T, key)) {
                    printf("该关键字不在平衡二叉树中。\n\n");
                    printf("请重新输入要分裂的关键字: ");
                } else {
                    BBSTree T1 = NULL;
                    BBSTree T2 = NULL;
                    SpiltBBST(T, key, T1, T2);
                    printf("\n----------------------------------------------------\n");
                    printf("第一棵子树为：", key);
                    ParenthesisPrintBBST(T1);
                    printf("\n显示如下：\n\n");
                    ConcaveTablePrintBBST(T1,1);
                    printf("\n----------------------------------------------------\n\n");

                    printf("\n----------------------------------------------------\n");
                    printf("第二棵子树为：", key);
                    ParenthesisPrintBBST(T2);
                    printf("\n显示如下：\n\n");
                    ConcaveTablePrintBBST(T2,1);
                    printf("\n----------------------------------------------------\n\n");
                    break;
                }
            }
        }
    }
}

/**
 * 合并平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void MergeBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树未创建\n");
    } else {
        if (NULL == T) {
            printf("原平衡二叉树为空，现在创建一棵平衡二叉树合并到此二叉树中\n");
        } else {
            printf("\n--------------------------------------- -------------");
            printf("\n现在平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n显示如下：\n\n");
            ConcaveTablePrintBBST(T,1);
            printf("\n----------------------------------------------------");
            printf("\n现在创建一棵平衡二叉树合并到此二叉树中\n\n");
        }
        BBSTree T1 = NULL;
        InsertAVLOperation(T1); 
        printf("\n----------------------------------------------------");
        printf("\n新平衡二叉树为：");
        ParenthesisPrintBBST(T1);
        printf("\n显示如下：\n\n");
        ConcaveTablePrintBBST(T1,1);
        printf("\n----------------------------------------------------\n\n");
        MergeBBST(T, T1);
        DestroyBBST(T1);
        printf("\n----------------------------------------------------");
        printf("\n合并后平衡二叉树为：");
        ParenthesisPrintBBST(T);
        printf("\n显示如下：\n\n");
        ConcaveTablePrintBBST(T,1);
        printf("\n----------------------------------------------------\n\n");
    }
}

/**
 * 销毁平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void DestroyBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        printf("平衡二叉树未创建，销毁失败\n");
    } else if (flag == HAVE_BEEN_CREATED){
        if (NULL == T) {
            printf("平衡二叉树为空，不用销毁\n");
        } else {
            printf("是否销毁平衡二叉树？（Y/y：是, 其他任意键为否）");
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
 * 测试主函数
 */
int main()
{
    system("color 03");
    int num; 
    BBSTree T;
    while (1) {
        AVLMenu();
        printf("请输入操作：");
        scanf("%d", &num);
        getchar();
        fflush(stdin);
        if (0 == num) {
            printf("\n是否退出？（Y/y：是, 其他任意键为否）");
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
                default: printf("请输入正确的值\n"); break;
            }
        }
        system("PAUSE");
        system("CLS"); // 清屏操作
    }
    system("PAUSE");
    getch();
    return 0;
}
