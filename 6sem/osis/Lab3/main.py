class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left_child = None
        self.right_child = None

    def insert(self, data):
        if data < self.data:
            if self.left_child is None:
                self.left_child = TreeNode(data)
            else:
                self.left_child.insert(data)
        elif data > self.data:
            if self.right_child is None:
                self.right_child = TreeNode(data)
            else:
                self.right_child.insert(data)

    def find_node(self, data):
        if data < self.data:
            if self.left_child is None:
                raise (f'Value {data} doesn\'t exist')
            return self.left_child.find_node(data)
        elif data > self.data:
            if self.right_child is None:
                raise (f'Value {data} doesn\'t exist')   
            return self.right_child.find_node(data)
        return self

    def show_tree(self):
        print(str(self))
        if self.left_child is not None:
            self.left_child.show_tree()
        if self.right_child is not None:
            self.right_child.show_tree()

    def clear(self):
        self.right_child = self.left_child = None
    
    def _delete(self, node, key):
        if node is None:
            return node

        if key < node.data:
            node.left_child = self._delete(node.left_child, key)
        elif key > node.data:
            node.right_child = self._delete(node.right_child, key)
        elif node.left_child is not None and node.right_child is None:
            node.data = min([node.data, key])
            node.right_child = self._delete(node.right_child, node.data)
        else:
            if node.left_child is not None:
                node = node.left_child
            elif node.right_child is not None:
                node = node.right_child
            else:
                node = None
        return node

    def delete(self, key):
        self = self._delete(self, key)

    def __str__(self):
        return str(self.data)       

if __name__ == '__main__':
    tree = TreeNode(12)
    tree.delete(10)

    tree.insert(10)
    tree.insert(13)
    tree.insert(15)
    tree.insert(16)
    print(tree.show_tree())
