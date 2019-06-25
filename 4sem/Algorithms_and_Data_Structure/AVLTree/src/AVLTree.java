import static java.lang.Integer.max;
/*
* CompareTo return < 0 if a < b
* else if a > b return > 0
* else 0
* a.compareTo(b)
*/


public class AVLTree<T extends Comparable> {
    public class AVLTreeNode<T> {
        AVLTreeNode<T> left;
        AVLTreeNode<T> right;

        T key;
        int height;

        public AVLTreeNode(T key) {
            this.key = key;
            height = 1;
        }
    }

    AVLTreeNode<T> root;

    private int nodeHeight(AVLTreeNode<T>  node) {
        return node == null ? 0 : node.height;
    }

    private int balanceFactor(AVLTreeNode<T> node) {
        return nodeHeight(node.right) - nodeHeight(node.left);
    }

    private void updateHeight(AVLTreeNode<T> node) {
        node.height = max(nodeHeight(node.right), nodeHeight(node.left)) + 1;
    }

    private AVLTreeNode<T> rotateRight(AVLTreeNode<T> node) {
        AVLTreeNode<T> temp = node.left;

        node.left = temp.right;
        temp.right = node;

        updateHeight(node);
        updateHeight(temp);

        return temp;
    }

    private AVLTreeNode<T> rotateLeft(AVLTreeNode<T> node) {
        AVLTreeNode<T> temp = node.right;

        node.right = temp.left;
        temp.left = node;

        updateHeight(node);
        updateHeight(temp);

        return temp;
    }

    private AVLTreeNode<T> balance(AVLTreeNode<T> node) {
        updateHeight(node);

        int difference = balanceFactor(node);

        switch (difference) {
            case 2:
                if (balanceFactor(node.right) < 0)
                    node.right = rotateRight(node.right);
                return rotateLeft(node);
            case -2:
                if (balanceFactor(node.left) > 0)
                    node.left = rotateLeft(node.left);
                return rotateRight(node);
            default:
                return node;
        }
    }

    private AVLTreeNode<T> insert(AVLTreeNode<T> node, T k) {
        if(node == null) return new AVLTreeNode<>(k);

        if(k.compareTo(node.key) <= 0) {
            node.left = insert(node.left, k);
        }
        else
            node.right = insert(node.right, k);
        return balance(node);
    }

    void push(T key) {
        root = insert(root, key);
    }

    private AVLTreeNode<T> findMin(AVLTreeNode<T> node) {
        return node.left == null ? node : findMin(node.left);
    }

    private AVLTreeNode<T> removeMin(AVLTreeNode<T> node) {
        if (node.left == null)
            return node.right;
        else
            node.left = removeMin(node.left);

        return balance(node);
    }

    void remove(T key) {
        root = removeNode(root, key);
    }

    private AVLTreeNode<T> removeNode(AVLTreeNode<T> node, T key) {
        if(node == null) return null;

        if (key.compareTo(node.key) < 0) {
            node.left = removeNode(node.left, key);
        } else if (key.compareTo(node.key) > 0) {
            node.right = removeNode(node.right, key);
        } else {
            //System.out.println("Node" + node.key );
            AVLTreeNode<T> left = node.left;
            AVLTreeNode<T> right = node.right;

            if (right == null)
                return left;

            //System.out.println("Right: " + right.key);
            //print();
            AVLTreeNode<T> min = findMin(right);
            //System.out.println("key: " + min.key);
            min.right = removeMin(right);
            min.left = left;

            return balance(min);
        }
        return balance(node);
    }

    public void print() {
        printTree(root, 0);
    }

    private void printTree(AVLTreeNode<T> node, int level) {
        if (node != null) {
            printTree(node.right,level + 1);
            for (int i=0; i < level; i++) {
                System.out.print("\t");
            }
            System.out.println("->" + node.key + " h=" + node.height);
            printTree(node.left,level + 1);
        }
    }

    AVLTreeNode<T> find(T key) {
        return getNode(root, key);
    }

    private AVLTreeNode<T> getNode(AVLTreeNode<T> node, T k) {
        if(node == null)
            throw new IllegalArgumentException("There is no node with such key");

        if (k.compareTo(node.key) == 0)
            return node;
        else if(k.compareTo(node.key) <= 0)
            return getNode(node.left, k);
        else
            return getNode(node.right, k);
    }

    AVLTreeNode<T> prev(T key) {
        AVLTreeNode<T> current = root, res = null;
        while (current != null) {
            if (key.compareTo(current.key) > 0) {
                res = current;
                current = current.right;
            } else {
                 current = current.left;
            }
        }
        if (res == null)
            throw new IllegalArgumentException("There is no elements smaller then: " + key);
        return res;
    }

    AVLTreeNode<T> next(T key) {
        AVLTreeNode<T> current = root, res = null;
        while (current != null) {
            if (key.compareTo(current.key) >= 0) {
                current = current.right;
            } else {
                res = current;
                current = current.left;
            }
        }
        if (res == null)
            throw new IllegalArgumentException("There is no elements bigger then " + key);
        return res;
    }

    void NLR() { // Прямой
        startNLR(root);
    }

    void LNR() { // Центрированный
        startLNR(root);
    }

    void LRN() { // Обратный
        startLRN(root);
    }
    
    private void startNLR(AVLTreeNode<T> node) {
        if (node != null) {
            System.out.print(node.key + " ");
            startNLR(node.left);
            startNLR(node.right);
        }
    }

    private void startLNR(AVLTreeNode<T> node) {
        if (node != null) {
            startLNR(node.left);
            System.out.print(node.key + " ");
            startLNR(node.right);
        }
    }

    private void startLRN(AVLTreeNode<T> node) {
        if (node != null) {
            startLRN(node.left);
            startLRN(node.right);
            System.out.print(node.key + " ");
        }
    }
}