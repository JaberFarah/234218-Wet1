//
//  Header.h
//  wet
//
//  Created by Amjad Watad on 11/26/14.
//  Copyright (c) 2014 Amjad Watad. All rights reserved.
//

#ifndef wet_Avl_h
#define wet_Avl_h
#include <iostream>
#include <stdlib.h>
using namespace std;



template<typename T,typename K>
class avlTree{
private:
    avlTree<T, K>* left;
    avlTree<T, K>* right;
    avlTree<T, K>* parent;
    K key;
    T data;
    T* mostPowerful;
    int height;

public:
//    avlTree(const T& data, const K& key, avlTree<T, K>* right, avlTree<T, K>* left, avlTree<T, K>* parent):right(right), left(left), parent(parent), key(key), data(data),mostPowerful(&(this->data)), height(0){}
//    avlTree():right(NULL), left(NULL), parent(NULL),key(), data(), mostPowerful(NULL), height(0){}

    avlTree(const T data,const K key) : left(NULL),right(NULL),parent(NULL),key(key),data(data),mostPowerful(&(this->data)),height(0){}
    avlTree() : left(NULL),right(NULL),parent(NULL),key(NULL),data(NULL),mostPowerful(NULL),height(0){}

    ~avlTree(){
        this->clear();
    }

    T* getMostPowerful()
    {
    	return this->mostPowerful;
    }



    //updated
    avlTree<T, K>* find(K key) {
    	if(this==NULL){
    		return NULL;
    	}
    	if(this->key==key){
    		return this;
    	}
    	if(this->key>key){
    		return left->find(key);
    	}
    	else return right->find(key);
    }
    		//updated
           void rotateRight(avlTree<T, K>* b){
               avlTree<T, K>* a = b->left;
               avlTree<T, K>* aRight = ( a == NULL ? NULL : a->right );//error
               if( b->parent != NULL){
            	   if(b->parent->right==b){
            		   b->parent->right=a;
            	   }
                   if (b->parent->left==b){
                       (b->parent)->left = a;
                   }
                   else throw"RotateRight avl";//this should never happen
               }
               b->left = aRight;
               a->right = b;
               a->parent = b->parent;
               b->parent = a;
               if( aRight){
                   aRight->parent = b;
               }
               updateMostPowerful(b);
               updateMostPowerful(a);
               LLupdate(b);
               LLupdate(a);
               return;
           }

           //updated
           void rotateLeft(avlTree<T, K>* a){
               avlTree<T, K>* b = a->right;
               avlTree<T, K>* bLeft = (b == NULL ? NULL : b->left);
               if(a->parent != NULL){
                   if(a->parent->right==a){
                       (a->parent)->right = b;
                   }
                   if(a->parent->left==a){
                       (a->parent)->left = b;
                   }
               }
               a->right = bLeft;
               b->left = a;
               b->parent = a->parent;
               a->parent = b;
               if ( bLeft){
                   bLeft->parent = a;
               }
               LLupdate(b);
               LLupdate(a);
               updateMostPowerful(a);
               updateMostPowerful(b);
               return;
           }

           //no longer needed
//            bool isRight(bool a){
//                return parent->right == this;
//            }
            //no longer needed
//            bool isLeft(bool a){
//                return parent->left == this;
//            }
            //updated
           void LRRotate(avlTree<T, K>* c){//b
               avlTree<T, K>* b = c->left;
               rotateLeft(b);
               rotateRight(c);
               return;
           }
           //updated
           void RLRotate(avlTree<T, K>* c){
               avlTree<T, K>* b = c->right;
               rotateRight(b);
               rotateLeft(c);
           }
           //updated
           void RRRotate(avlTree<T, K>* a){
               rotateLeft(a);
               return;
           }
           //updated
           void LLRotate(avlTree<T, K>* a){
               rotateRight(a);
               return;
           }
           int treeHeight(avlTree<T, K>* a){
               if(a == NULL){
                   return 0;
               }
               return 1 + max(treeHeigt(a->left), (treeHeight(a->right)));
           }
            int max(int x, int y){
                return x > y ? x : y;
            }


//first searches for the key, if found, it throws an error, else it attempts to insert it.
//might throw an error when allocating so catch
    //updated
    void insert(T data, K key){
        if(find(key)!=NULL){
            throw "keyAlreadyExists";
        }
        avlTree<T, K>* newNode = new avlTree<T, K>(data,key);
        addNode(newNode, this);
        updateHeight(newNode->parent, newNode);
        updateMax(newNode->parent, newNode->mostPowerful);
        rebalance(newNode->parent, true);

    }

    //updated
    void addNode(avlTree<T, K>* newNode, avlTree<T, K>* parent){
    	if(parent->parent==NULL && parent->mostPowerful==NULL){//may cause memory leak
    		parent=newNode;
    	}
    	if(this==NULL){
    		if(parent->key>newNode->key){
    			parent->left=newNode;
    		}
    		else{
    			parent->right=newNode;
    		}
		newNode->parent=parent;
    	}
    	else{
    		if(parent->key>newNode->key){
    			parent->left->addNode(newNode, this);
    		}
    		else{
    			parent->right->addNode(newNode,this);
    		}
    	}

//        avlTree<T, K>* wanted = find((n->);
//        v->parent = wanted;
//        if(wanted->parent == NULL){
//            wanted->left = v;
//            wanted->right = v;
//
//        } else {
//            if((wanted->data) > (v->data)){
//                wanted->left = v;
//            } else{
//                wanted->right = v;
//            }
//        }
//        updateHeight(v);
//        checkAndRotate(v);
//        findMaxAndUpdate(this);

    }

    void remove(T data,avlTree<T,K>** root, avlTree<T, K>* dontUseFind = NULL){
        avlTree<T, K>* toRemove;
        if(dontUseFind == NULL){
            toRemove = find(data);
        } else{
            toRemove = dontUseFind;
        }
        if(toRemove == NULL){
            throw DataIsNotExisted();
        }
        avlTree<T, K>* toRemoveRight = toRemove->right;
        avlTree<T, K>* toRemoveLeft = toRemove->left;
        avlTree<T, K>* toRemoveParent = toRemove->parent;
        avlTree<T, K>* toRemoveNext = NULL;
        if(toRemoveRight == NULL && toRemoveLeft == NULL){
        	if(toRemove->parent==NULL){//added
        		delete this->data;
        		delete this->key;
        		this->mostPowerful==NULL;
        	}
            if(toRemove->parent->right==toRemove){
                toRemoveParent->right = NULL;
            }
            if(toRemove->parent->left==toRemove){
                toRemoveParent->left = NULL;
            }
        } else if(toRemoveRight == NULL){// then left is not NULL
            if(toRemove->parent->right==toRemove){
                toRemoveParent->right = toRemoveLeft;
                toRemoveLeft->parent=toRemove->parent;
            }
            if(toRemove->parent->left==toRemove){//changed
                toRemoveParent->left = toRemoveLeft;
            }
            toRemoveLeft->parent = toRemoveParent;
        } else if(toRemoveLeft == NULL){// right is not NULL
            if(toRemove->parent->right==toRemove){
                toRemoveParent->right = toRemoveRight;
            }
            if(toRemove->parent->left==toRemove){
                toRemoveParent->left = toRemoveRight;
            }
            toRemoveRight->parent = toRemoveParent;
        } else{ // right and left are not NULL
            toRemoveNext = toRemove->next();
            swapTwoVertexes(toRemove, toRemoveNext);
            remove(toRemoveNext->data, toRemoveNext);//toRemove_next
            updateMostPowerful(toRemoveNext);//added
//            findMaxAndUpdate(this);
            return;
        }//so far so good

        if(toRemoveLeft != NULL || toRemoveRight != NULL) {
            updateParentHeight(toRemoveRight);
            updateParentHeight(toRemoveLeft);//ok
        } else if(toRemoveParent != NULL){
        	updateHeight(toRemoveParent);
//            toRemoveParent->height = 1 + max(getHeight(toRemoveParent->left), getHeight(toRemoveParent->right));
            updateParentHeight(toRemoveParent);
        }

        if(toRemoveRight != NULL){
        	rebalance(toRemoveRight, false);
//            checkAndRotate(toRemoveRight, false);
        } else if(toRemoveLeft != NULL){
        	rebalance(toRemoveLeft, false);//added
//            checkAndRotate(toRemoveLeft, false);
        } if(!isRoot(toRemoveParent)){
        	rebalance(toRemoveParent, false);
//            checkAndRotate(toRemoveParent, false);
        }
        updateMostPowerful(this);
//        findMaxAndUpdate(this);
        toRemove->right = NULL;
        toRemove->left = NULL;
        delete toRemove;
    }

    //updated
    void swapTwoNodes(avlTree<T, K>* v1, avlTree<T, K>* v2){
          T tmpData = v1->data;
          K tmpKey = v1->key;
          v1->data = v2->data;//
          v1->key = v2->key;
          v1->mostPowerful = &(v2->data);
          v2->data = tmpData;
          v2->key = tmpKey;
          v2->mostPowerful = &tmpData;
        return;
    }

    avlTree<T, K>* next(){
        avlTree<T, K>* tmp = right;
        while(tmp->left != NULL){
            tmp = tmp->left;
        }
        return tmp;
    }

    bool isRoot(avlTree<T, K>* v){
        return v->parent == NULL;
    }

    	//upadeted
    void updateHeight(avlTree<T, K>* n){
    	if(n!=NULL){
    		n->height=1+max(getHeight(n->left), getHeight(n->right));
    	}
    }

    //ok
    void updateParentHeight(avlTree<T, K>* v){
        if (v == NULL || v->parent==NULL){
            return;
        }
        while(v->parent!=NULL){
        	updateHeight(v->parent);
        	v=v->parent;
        }
    }

    //added
    void updateSubHeight(avlTree<T,K>* n){
    	if(n!=NULL){
    		if(n->right!=NULL){
    			updateHeight(n->right);
    		}
    		if(n->left!=NULL){
    			updateHeight(n->left);
    		}
    		return;
    	}
    	throw"updateSubHeight NULL Argument";
    }

    //update height down->top
    void updateHeight(avlTree<T, K>* parent, avlTree<T,K>* node){
        if (parent==NULL || (parent->height >= node->height+1)){
        	return;
        }
        parent->height = node->height + 1;
        updateHeight(parent->parent, parent);
//        avlTree<T, K>* tmp = node->parent;
//        node->height = 0;
//        count++;
//        tmp = tmp->parent;
//        while(tmp->parent != NULL && count != tmp->height){
//            tmp->height = height > count ? height : count;
//            tmp = tmp->parent;
//            count++;
//        }
    }



    //unused function?
//    void updateHeightAfterRemove(avlTree<T, K>* v){
//        int count = 0;
//        avlTree<T, K>* tmp;
//        v->height = 0;
//        if(v->right != NULL){
//            tmp = v->right;
//        } else if(v->left != NULL){
//            tmp = v->left;
//        } else{
//            tmp = v->parent;
//        }
//        count++;
//        while(!isRoot(tmp)  && count != tmp->height){
//            if(tmp->isRight()){
//               tmp->parent->height = (1 + getHeight(v->left)) > count ? 1 + getHeight(v->left) : count;
//            } else{
//                tmp->parent->height = (1 + getHeight(v->right)) > count ? 1 + getHeight(v->left) : count;
//            }
//            tmp = tmp->parent;
//            count++;
//        }
//    }

    //bf = balance factor
    //updated
    //update 2: boolean variable is true if the function is called after an insert and false if called after remove
    void rebalance(avlTree<T, K>* node, bool afterInsert){

        int balanceFactor;
        //this works because its not a recursive function
        if(node->parent->right !=NULL && node->parent->left != NULL && afterInsert){
        	return;
        }
        while(node->parent != NULL){

        	balanceFactor = getBF(node);
            if(balanceFactor == 2){
            	if(getBF(node->left) >= 0){
                    LLRotate(node);
                } else{
                    LRRotate(node);
                }
            } else if(balanceFactor == -2){
                    if(getBF(node->right)==1){
                        RLRotate(node);
                    } else{
                        RRRotate(node);
                    }
            } else{
                node = node->parent;
                continue;
            }
            updateHeightAfterRotation(node);//ok
            node = node->parent;
        }
    }

    ///updated
    int getBF(avlTree<T, K>* n){
    	if(n==NULL){
    		return 0;
    	}
        int leftHeight = n->left == NULL ? 0 : (n->left)->height+1;
        int rightHeight = n->right == NULL ? 0 : (n->right)->height+1;
        return leftHeight - rightHeight;
    }


    //updates the height of the parent and the node itself
    void updateHeightAfterRotation(avlTree<T, K>* v){
    	if(v==NULL){
    		throw "NULL updateHeightAfterRotation avl";
    	}
        updateSubHeight(v);//ok
        updateHeight(v);
//        v->height = 1 + max(getHeight(v->left), getHeight(v->right)); //ok
        if(v->parent!=NULL){
            if(v->parent->left != NULL && v->parent->left!=v){//ok
            	updateHeight(v->parent->left);
//                v->parent->left->height = 1 + max(getHeight(v->parent->left->left), getHeight(v->parent->left->right));
            }
            if(v->parent->right != NULL && v->parent->right!=v){//ok error?
            	updateHeight(v->parent->right);
//                v->parent->right->height = 1 + max(getHeight(v->parent->right->left), getHeight(v->parent->right->right));
            }
            updateHeight(v->parent);
//            v->parent->height = 1 + max(getHeight(v->parent->left), getHeight(v->parent->right));
        }
        updateParentHeight(v);//ok
    }

    void LLupdate(avlTree<T, K>* v){
    	updateHeight(v);
//        v->height =1 + max(getHeight(v->left), getHeight(v->right));

    }

    //returns the height of a node or 0 if its a null
    int getHeight(avlTree<T, K>* v){
        if(v == NULL){
            return 0;
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
            cout << data << " BF: " << getBF(this) << " height: " << height << endl;
            right->printInOrder();
        }

    }

    void clear(){
      /*  while(this->right != NULL){
            this->remove(this->right->getData());
        }*/
    }

    T getFirstData(){
        if(right == NULL){
            throw TreeIsEmpty();
        }
        return right->data;
    }

    T getData(){
        return data;
    }

//    void updateData(T oldValue, T newValue){
//        remove(oldValue);
//        insert(newValue);
//        return;
//    }

    //added
    //updates most powerful for a given subtree
    void updateMostPowerful(avlTree<T,K> *node){
    	if(!(node==NULL)){
    		if(node->left!=NULL){
    			if(node->right!=NULL){
    				T* mostPowerful = (*(node->left->mostPowerful)>*(node->right->mostPowerful))?node->left->mostPowerful:node->right->mostPowerful;
    				if(mostPowerful->getPower()-node->data.getPower()>0){
    					node->mostPowerful=mostPowerful;
    				}
    			}
    			if(node->mostPowerful->getPower()-node->left->mostPowerful->getPower()<0){
    				node->mostPowerful=node->left->mostPowerful;
    				return;
    			}
    		}
    		if(node->right!=NULL && node->mostPowerful->getPower()-node->right->mostPowerful->getPower()<0){
				node->mostPowerful=node->right->mostPowerful;
				return;
    		}
    	}
    }

    void updateMax(avlTree<T, K>* node, T* max){
        if(node==NULL || *(node->mostPowerful)>*(max)){
        	return;
        }
        else{
        	(node->mostPowerful)=max;
        	updateMax(node->parent, max);
        }

//            if(node->right == NULL){
//                return;//throw TreeIsEmpty();
//            } else{
//                this->findMaxAndUpdate(node->right);
//            }
//        else{
//            if(node->right == NULL){
//                this->maxData = node->getData();
//            } else{
//                this->findMaxAndUpdate(node->right);
//            }
//        }
    }


    //unused--no longer needed
//    T getMaxData(){
//        return maxData;
//    }

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

    void avlToArray(T** array, int* n){
        int numOfData = this->getNumOfData();
        *n = numOfData;
        if(numOfData == 0){
            return;
        }

        *array = new T[numOfData];
        avlTree<T, K>* tmpTree = right;
        int num = 0;
        auxAvlToArray(tmpTree, *array, &num);
        return;
    }

    void auxAvlToArray(avlTree<T, K>* v, T* array, int* n){
        if(v->right != NULL){
            auxAvlToArray(v->right, array, n);
        }
        array[*n] = v->data;
        *n += 1;
        if(v->left == NULL){
            return;
        } else{
            auxAvlToArray(v->left, array, n);
        }
        return;
    }

    void arrayToAvl(T* array){
        int numberOfApps = this->getNumOfData();
        if(numberOfApps == 0){
            return;
        }
        int n = 0;
        avlTree<T, K>* tmp = this->right;
        auxArrayToAvl(tmp, array, &n);
    }

    void auxArrayToAvl(avlTree<T, K>* v, T* array, int* n){
        if(v->right != NULL){
            auxArrayToAvl(v->right, array, n);
        }
        v->data = array[*n];
        *n += 1;
        if(v->left == NULL){
            return;
        } else{
            auxArrayToAvl(v->left, array, n);
        }
        return;
    }

    void mergeTwoArrays(T* array1,int n1,T* array2,int n2,T* result){
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

    avlTree<T, K>* getRight(){
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

#endif
