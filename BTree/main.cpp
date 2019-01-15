#include <iostream>
#include "main.h"
#include "BTree.h"

using namespace std;

int status = NOT_INIT; //全局变量 

/**
 * 初始化一棵B树
 *
 * @param t B树
 */
void InitBTreeOperation(BTree &t) {
    if (status == HAVE_BEEN_INIT) {
       printf("B树在之前已经创建，请不要重复创建操作\n"); 
       return; 
    }
    printf("\nB树创建成功，初始为空树\n");
    status = HAVE_BEEN_INIT;
}

/**
 * 插入结点操作
 *
 * @param t B树
 */
void InsertKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == status) {
        printf("B树未初始化\n");
        return;
    }
    if (NULL == t) {
        printf("B树为空\n");
    } else {
        printf("B树的凹入表显示如下：\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
    }
    while (1) {
        printf("请输入想插入的关键字：");
        while (1 != scanf("%d", &key)) {
            getchar();
            fflush(stdin);
            printf("请输入正确的值！\n");
            printf("请输入想插入的关键字：");
        }
        SearchBTree(t, key, r);
        if (1 == r.tag) {
            printf("关键字已经存在\n");
        } else if (0 == r.tag) {
            InsertBTree(t, key, r.pt, r.i);
            printf("插入后B-树如下：\n");
            printf("------------------------------------------------------\n");
            PrintBTree(t, 1);
            printf("\n------------------------------------------------------\n");
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

/**
 * 删除结点操作
 *
 * @param t B树
 */
void DeleteKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == status) {
        printf("B树未初始化\n");
        return;
    }
    if (NULL == t) {
        printf("B树为空，删除失败\n");
        return;
    } else {
        printf("B树的凹入表显示如下：\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        while (1) {
            printf("请输入想删除的关键字：");
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                printf("请输入正确的值\n");
                printf("请输入想删除的关键字：");
            }
            SearchBTree(t, key, r);
            if (1 == r.tag) {
                DeleteBTree(t, r.pt, r.i);
                if (BTreeKeyNumber(t) == 0) {
                    t = NULL;
                    printf("B树的关键字已经全部删除\n");
                    break;
                } else {
                    printf("删除后B-树如下：\n");
                    printf("------------------------------------------------------\n");
                    PrintBTree(t, 1);
                    printf("\n------------------------------------------------------\n");
                }
            } else if (0 == r.tag) {
                printf("关键字不在B树中，删除失败\n");
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

/**
 * 查找结点操作
 *
 * @param t B树
 */
void SearchOperation(BTree t) {
    KeyType key;
    Result r;
    if (NOT_INIT == status) {
        printf("B树未初始化\n");
        return;
    }
    if (NULL == t) {
        printf("B树为空，查找失败\n");
        return;
    } else {
        printf("B树的凹入表显示如下：\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        printf("请输入要查找的关键字：");
        scanf("%d", &key);
        SearchBTree(t, key, r);
        if (0 == r.tag) {
            printf("没有查到该关键字\n");
        } else {
            printf("以关键字所在结点的子树如下：\n");
            printf("------------------------------------------------------\n");
            PrintBTree(r.pt, 1);
            printf("\n------------------------------------------------------\n");
        }
    }
}



/**
 * 顺序输出B树操作
 *
 * @param t B树
 */
void OrderTraverseBTreeOperation(BTree t) {
    if (NOT_INIT == status) {
        printf("B树未初始化\n");
    } else if (NULL == t) {
        printf("B树为空\n");
    } else {
        printf("B树有%d个关键字，输出如下：\n", BTreeKeyNumber(t));
        OrderTraverseBTree(t);
        printf("\n");
    }
}

/**
 * 凹入表打印B树操作
 *
 * @param t B树
 */
void PrintBTreeOperation(BTree t) {
    if (NOT_INIT == status) {
        printf("B树未初始化\n");
    } else if (NULL == t) {
        printf("B树为空\n");
    } else {
        printf("B树的凹入表显示如下：\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 8);
        printf("\n------------------------------------------------------\n");
    }
}

/**
 * 随机生成指定大小的B树
 *
 * @param t B树
 */
void CreateBTreeRandomOperation(BTree &t) {
    if (status == HAVE_BEEN_INIT) {
        printf("之前已经有B树创建，因此该操作失败\n");   
            return;
    }
    printf("输入生成的B树关键字数量（只支持1-100的输入）：");
    int keyNumber;
    while (1) {
        int result = scanf("%d", &keyNumber);
        getchar();
        fflush(stdin);
        if (result == 1) {
            if (keyNumber >= 1 && keyNumber <= 100) {
                break;
            }
        }
        printf("请输入正确的值\n");
        printf("请输入生成的B树关键字数量（只支持1-100的输入）：");
    }
    CreateBTreeRandom(t, keyNumber);
    printf("\n生成成功，下面是B树的凹入表显示：\n");
    printf("------------------------------------------------------\n");
    PrintBTree(t, 1);
    printf("\n------------------------------------------------------\n");
    status = HAVE_BEEN_INIT;
}

/**
 * 销毁B树操作
 *
 * @param t B树
 */
void DestoryBTreeOperation(BTree &t) {
    if (status == NOT_INIT) {
        printf("B树还没创建，不用销毁\n");
    } else if (t == NULL) {
        printf("B树为空，不用销毁\n");
    } else {
        DestoryBTree(t);
        status = NOT_INIT;
        printf("销毁成功\n");
    }
}

/**
 * B-树功能演示选择菜单
 */
void BTreeMenu() {
    system("color 03");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("*************************** B树功能选择菜单*******************************\n");
    printf("*                                                                        *\n");
    printf("**************** 17级网络工程2班  黄贤淦（3117005073）  ******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. 创建一棵空B-树                              *\n");
    printf("*                         2. 初始化一棵B-树                              *\n");
    printf("*                         3. 插入关键字                                  *\n");
    printf("*                         4. 删除关键字                                  *\n");
    printf("*                         5. 查找关键字                                  *\n");
    printf("*                         6. 关键字数量                                  *\n");
    printf("*                         7. 升序输出B-树关键字                          *\n");
    printf("*                         8. 凹入表打印B-树                              *\n");
    printf("*                         9. 销毁B-树                                    *\n");
    printf("*                         0. 退出                                        *\n");
	printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}

/**
 * 主函数
 */
int main()
{
    BTree t;
    int num;
    while (1) {
        BTreeMenu();
        printf("请输入您的选择：");
        scanf("%d", &num);
        getchar();
        fflush(stdin);
        if (0 == num) {
            printf("\n是否退出？（Y：是, 其他任意键为否）");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (status == HAVE_BEEN_INIT) {
                    DestoryBTree(t);
                }
                exit(-1);
            }
        } else {
            switch (num) {
                case 1: InitBTreeOperation(t); break;
                case 2: CreateBTreeRandomOperation(t); break;
                case 3: InsertKeyOperation(t); break;
                case 4: DeleteKeyOperation(t); break;
                case 5: SearchOperation(t); break;
                case 6: {
                    if (NOT_INIT == status) {
                        printf("B树未初始化\n");
                    } else {
                        printf("\n关键字数量为: %d\n", BTreeKeyNumber(t));
                    }
                    break;
                }
                case 7: OrderTraverseBTreeOperation(t); break;
                case 8: PrintBTreeOperation(t); break;
                case 9: DestoryBTreeOperation(t); break;
                
                default: printf("请输入正确的值\n"); break;
            }
        }
        system("PAUSE");
        system("cls"); // 清屏操作
    }
    system("PAUSE");
    getch();
    return 0;
}

