/*
 * avlTree.h
 *
 *  Created on: May 9, 2017
 *      Author: admin
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_


#include <iostream>
#include <stdlib.h>
using namespace std;



template<typename DataType>
class avlTree{
private:
    avlTree<DataType>* right;
    avlTree<DataType>* left;
    avlTree<DataType>* parent;
    DataType app;
    DataType maxData;
    int height;

public:
    avlTree(DataType app):right(NULL), left(NULL), parent(NULL), app(app),maxData(app), height(0){}
    avlTree():right(NULL), left(NULL), parent(NULL), app(), maxData(), height(0){}


    ~avlTree(){
        this->clear();
    }





    avlTree<DataType>* find(DataType app, bool insert) {
        if( parent == NULL && ( right == NULL || left == NULL )){
            return insert ? this : NULL;
        }
        if(parent == NULL){
            return right->find(app, insert);
        }
        if((this->app) == app){
            if(!insert){
                return this;
            } else{
                throw Fail();
            }
        }
        if(app > (this->app)){
            if(right == NULL){
                if(insert){
                    return this;
                } else{
                    return NULL;
                }
            }
        return right->find(app, insert);
        } else{
            if(left == NULL){
                if(insert){
                    return this;
                } else{
                    return NULL;
                }
            }
        return left->find(app, insert);
        }
        return NULL;
    }

           void rightRotate(avlTree<DataType>* b){
               avlTree<DataType>* a = b->left;
               avlTree<DataType>* a_right = ( a == NULL ? NULL : a->right );//error
               if( b->parent != NULL){
                   if(b->isRight()){
                       (b->parent)->right = a;
                   }
                   if(b->isLeft()){
                       (b->parent)->left = a;
                   }
               }
               b->left = a_right;
               a->right = b;
               a->parent = b->parent;
               b->parent = a;
               if( a_right){
                   a_right->parent = b;
               }
               LLupdate(b);
               LLupdate(a);
               return;
           }

           void leftRotate(avlTree<DataType>* a){
               avlTree<DataType>* b = a->right;
               avlTree<DataType>* b_left = (b == NULL ? NULL : b->left);
               if(a->parent != NULL){
                   if(a->isRight()){
                       (a->parent)->right = b;
                   }
                   if(a->isLeft()){
                       (a->parent)->left = b;
                   }
               }
               a->right = b_left;
               b->left = a;
               b->parent = a->parent;
               a->parent = b;
               if ( b_left){
                   b_left->parent = a;
               }
               LLupdate(a);
               LLupdate(b);
               return;
           }

            bool isRight(){
                return parent->right == this;
            }
            bool isLeft(){
                return parent->left == this;
            }

           void leftRightRotate(avlTree<DataType>* c){//b
               avlTree<DataType>* b = c->left;
               leftRotate(b);
               rightRotate(c);
               return;
           }

           void rightLeftRotate(avlTree<DataType>* c){
               avlTree<DataType>* b = c->right;
               rightRotate(b);
               leftRotate(c);
           }

           void rightRightRotate(avlTree<DataType>* a){
               leftRotate(a);
               return;
           }
           void leftLeftRotate(avlTree<DataType>* a){
               rightRotate(a);
               return;
           }
           int treeHeight(avlTree<DataType>* a){
               if(a == NULL){
                   return 0;
               }
               return 1 + max(treeHeigt(a->left), (treeHeight(a->right)));
           }
            int max(int x, int y){
                return x > y ? x : y;
            }

    void insert(DataType app){
        if(find(app,false) != NULL){
            throw DataAlreadyExisted();
        }
            avlTree<DataType>* application = new avlTree<DataType> (app);
            addApp(application);
    }



    void addApp(avlTree<DataType>* v){
        avlTree<DataType>* wanted = find((v->app), true);
        v->parent = wanted;
        if(wanted->parent == NULL){
            wanted->left = v;
            wanted->right = v;

        } else {
            if((wanted->app) > (v->app)){
                wanted->left = v;
            } else{
                wanted->right = v;
            }
        }
        updateHeight(v);
        checkAndRotate(v);
        findMaxAndUpdate(this);

    }

    void remove(DataType app, avlTree<DataType>* dontUseFind = NULL){
        avlTree<DataType>* toRemove;
        if(dontUseFind == NULL){
            toRemove = find(app, false);
        } else{
            toRemove = dontUseFind;
        }
        if(toRemove == NULL){
            throw DataIsNotExisted();
        }
        avlTree<DataType>* toRemove_Right = toRemove->right;
        avlTree<DataType>* toRemove_Left = toRemove->left;
        avlTree<DataType>* toRemove_parent = toRemove->parent;
        avlTree<DataType>* toRemove_next = NULL;
        if(toRemove_Right == NULL && toRemove_Left == NULL){
            if(toRemove->isRight()){
                toRemove_parent->right = NULL;
            }
            if(toRemove->isLeft()){
                toRemove_parent->left = NULL;
            }
        } else if(toRemove_Right == NULL){// then left is not NULL
            if(toRemove->isRight()){
                toRemove_parent->right = toRemove_Left;
            }
            if(toRemove->isLeft()){
                toRemove_parent->left = toRemove_Left;
            }
            toRemove_Left->parent = toRemove_parent;
        } else if(toRemove_Left == NULL){// right is not NULL
            if(toRemove->isRight()){
                toRemove_parent->right = toRemove_Right;
            }
            if(toRemove->isLeft()){
                toRemove_parent->left = toRemove_Right;
            }
            toRemove_Right->parent = toRemove_parent;
        } else{ // right and left are not NULL
            toRemove_next = toRemove->next();
            swapTwoVertexes(toRemove, toRemove_next);
            remove(toRemove_next->app, toRemove_next);//toRemove_next
            findMaxAndUpdate(this);
            return;
        }

        if(toRemove_Left != NULL || toRemove_Right != NULL) {
            updateParentHeight(toRemove_Right);
            updateParentHeight(toRemove_Left);
        } else if(toRemove_parent != NULL){
            toRemove_parent->height = 1 + max(getHeight(toRemove_parent->left), getHeight(toRemove_parent->right));
            updateParentHeight(toRemove_parent);
        }

        if(toRemove->right != NULL){
            checkAndRotate(toRemove_Right, false);
        } else if(toRemove->left != NULL){
            checkAndRotate(toRemove_Left, false);
        } if(!isRoot(toRemove_parent)){
            checkAndRotate(toRemove_parent, false);
        }
        findMaxAndUpdate(this);
        toRemove->right = NULL;
        toRemove->left = NULL;
        delete toRemove;
    }

    void swapTwoVertexes(avlTree<DataType>* v1, avlTree<DataType>* v2){
          DataType tmp_app = v1->app;
          v1->app = v2->app;//
          v2->app = tmp_app;
        return;
    }

    avlTree<DataType>* next(){
        avlTree<DataType>* tmp = right;
        while(tmp->left != NULL){
            tmp = tmp->left;
        }
        return tmp;
    }

    bool isRoot(avlTree<DataType>* v){
        return v->parent == NULL;
    }
    void updateParentHeight(avlTree<DataType>* v){
        if (v == NULL || isRoot(v)){
            return;
        }
        avlTree<DataType>* tmp = v;
        while(!isRoot(tmp->parent)){
            if(tmp->isRight()){
                tmp->parent->height = 1 + max(getHeight(tmp), getHeight(tmp->parent->left));
            } else{
                tmp->parent->height = 1 + max(getHeight(tmp), getHeight(tmp->parent->right));
            }
            tmp=tmp->parent;
        }
        return;
    }
    //update height down->top
    void updateHeight(avlTree<DataType>* v){
        int count = 0;
        avlTree<DataType>* tmp = v;
        v->height = 0;
        count++;
        tmp = tmp->parent;
        while(tmp->parent != NULL && count != tmp->height){
            tmp->height = height > count ? height : count;
            tmp = tmp->parent;
            count++;
        }
    }



    void updateHeightAfterRemove(avlTree<DataType>* v){
        int count = 0;
        avlTree<DataType>* tmp;
        v->height = 0;
        if(v->right != NULL){
            tmp = v->right;
        } else if(v->left != NULL){
            tmp = v->left;
        } else{
            tmp = v->parent;
        }
        count++;
        while(!isRoot(tmp)  && count != tmp->height){
            if(tmp->isRight()){
               tmp->parent->height = (1 + getHeight(v->left)) > count ? 1 + getHeight(v->left) : count;
            } else{
                tmp->parent->height = (1 + getHeight(v->right)) > count ? 1 + getHeight(v->left) : count;
            }
            tmp = tmp->parent;
            count++;
        }
    }

    void checkAndRotate(avlTree<DataType>* v, bool insert = true){
        avlTree<DataType>* tmp = v;
        int firstBf;
        int secondBf;
        if(v->parent->right != NULL && v->parent->left != NULL && insert){
            return;
        }
        while(tmp->parent != NULL){
            firstBf = getBF(tmp);
            if(firstBf > 1){
                secondBf = getBF(tmp->left);
                if(secondBf >= 0){
                    leftLeftRotate(tmp);
                } else{
                    leftRightRotate(tmp);
                }
            } else if(firstBf < -1){
                    secondBf = getBF(tmp->right);
                    if(secondBf > 0){
                        rightLeftRotate(tmp);
                    } else{
                        rightRightRotate(tmp);
                    }
            } else{
                tmp = tmp->parent;
                continue;
            }
            updateHeightAfterRotation(tmp);
            tmp = tmp->parent;
        }
    }

    int getBF(avlTree<DataType>* v){
        int leftHeight, rightHeight;
        leftHeight = v->left == NULL ? -1 : (v->left)->height;
        rightHeight = v->right == NULL ? -1 : (v->right)->height;
        return leftHeight - rightHeight;
    }

    void updateHeightAfterRotation(avlTree<DataType>* v){
        v->height = 1 + max(getHeight(v->left), getHeight(v->right));
        if(v->parent->left != NULL){
            v->parent->left->height = 1 + max(getHeight(v->parent->left->left), getHeight(v->parent->left->right));
        }
        if(v->parent->right != NULL){//???
            v->parent->right->height = 1 + max(getHeight(v->parent->right->left), getHeight(v->parent->right->right));
        }
        v->parent->height = 1 + max(getHeight(v->parent->left), getHeight(v->parent->right));
        updateParentHeight(v);
    }

    void LLupdate(avlTree<DataType>* v){
        v->height =1 + max(getHeight(v->left), getHeight(v->right));

    }

    int getHeight(avlTree<DataType>* v){
        if(v == NULL){
            return -1;
        }
        return v->height;
    }

    void printInOrder(){
        if( this == NULL){
            return;
        }
        if( parent == NULL ){
            right->printInOrder();
        } else{
            left->printInOrder();
            cout << app << " BF: " << getBF(this) << " height: " << height << endl;
            right->printInOrder();
        }

    }

    void clear(){
        while(this->right != NULL){
            this->remove(this->right->getData());
        }
    }

    DataType getFirstData(){
        if(right == NULL){
            throw TreeIsEmpty();
        }
        return right->app;
    }

    DataType getData(){
        return app;
    }

    void updateData(DataType oldValue, DataType newValue){
        remove(oldValue);
        insert(newValue);
        return;
    }

    void findMaxAndUpdate(avlTree<DataType>* v){
        if(isRoot(v)){
            if(v->right == NULL){
                return;//throw TreeIsEmpty();
            } else{
                this->findMaxAndUpdate(v->right);
            }
        }else{
            if(v->right == NULL){
                this->maxData = v->getData();
            } else{
                this->findMaxAndUpdate(v->right);
            }
        }
        return;
    }

    DataType getMaxData(){
        return maxData;
    }

    bool isEmpty(){
        return right == NULL && left == NULL;
    }

    int getNumOfData(){
        if( this == NULL){
            return 0;
        }
        if( parent == NULL ){
            return right->getNumOfData();
        } else{
            return 1+ left->getNumOfData() + right->getNumOfData();
        }
    }

    void avlToArray(DataType** array, int* n){
        int numOfData = this->getNumOfData();
        *n = numOfData;
        if(numOfData == 0){
            return;
        }

        *array = new DataType[numOfData];
        avlTree<DataType>* tmpTree = right;
        int num = 0;
        auxAvlToArray(tmpTree, *array, &num);
        return;
    }

    void auxAvlToArray(avlTree<DataType>* v, DataType* array, int* n){
        if(v->right != NULL){
            auxAvlToArray(v->right, array, n);
        }
        array[*n] = v->app;
        *n += 1;
        if(v->left == NULL){
            return;
        } else{
            auxAvlToArray(v->left, array, n);
        }
        return;
    }

    void arrayToAvl(DataType* array){
        int numberOfApps = this->getNumOfData();
        if(numberOfApps == 0){
            return;
        }
        int n = 0;
        avlTree<DataType>* tmp = this->right;
        auxArrayToAvl(tmp, array, &n);
    }

    void auxArrayToAvl(avlTree<DataType>* v, DataType* array, int* n){
        if(v->right != NULL){
            auxArrayToAvl(v->right, array, n);
        }
        v->app = array[*n];
        *n += 1;
        if(v->left == NULL){
            return;
        } else{
            auxArrayToAvl(v->left, array, n);
        }
        return;
    }

    void mergeTwoArrays(DataType* array1,int n1,DataType* array2,int n2,DataType* result){
        int index1,index2,index3;
        index1 = index2 = index3 = 0;
        while((index1 < n1) && (index2 < n2)){
            if((array1[index1] > array2[index2])){
                result[index3] = array1[index1];
                index1++;
            }
            else{
                result[index3] = array2[index2];
                index2++;
            }
            index3++;
        }
        while(index1 < n1){
            result[index3] = array1[index1];
            index1++;
            index3++;
        }
        while(index2 < n2){
            result[index3] = array2[index2];
            index2++;
            index3++;
        }
        return ;
    }

    avlTree<DataType>* getRight(){
        return right;
    }

    class Success{};
    class Fail{};
    class AllocError{};
    class TreeIsEmpty{};
    class InvalidInput{};
    class DataIsNotExisted{};
    class DataAlreadyExisted{};



};

#endif /* AVLTREE_H_ */
