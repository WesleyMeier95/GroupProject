#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "math.h"


using namespace std;

typedef struct splay {
int data;
struct splay* left;
struct splay* right;
struct splay* parent;
}splay;

splay* root = NULL;

 class SplayTree
{
public:
    SplayTree()
    {
    }

    // RR(Y rotates to the right)
    splay* RR_Rotate(splay* k2)
    {
        splay* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    // LL(Y rotates to the left)
    splay* LL_Rotate(splay* k2)
    {
        splay* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        return k1;
    }

    // An implementation of top-down splay tree
    splay* Splay(int data, splay* root)
    {
        if (!root)
            return NULL;
        splay header;
        /* header.right points to L tree;
        header.left points to R Tree */
        header.left = header.right = NULL;
        splay* LeftTreeMax = &header;
        splay* RightTreeMin = &header;
        while (1)
        {
            if (data < root->data)
            {
                if (!root->left)
                    break;
                if (data < root->left->data)
                {
                    root = RR_Rotate(root);
                    // only zig-zig mode need to rotate once,
                    if (!root->left)
                        break;
                }
                /* Link to R Tree */
                RightTreeMin->left = root;
                RightTreeMin = RightTreeMin->left;
                root = root->left;
                RightTreeMin->left = NULL;
            }
            else if (data > root->data)
            {
                if (!root->right)
                    break;
                if (data > root->right->data)
                {
                    root = LL_Rotate(root);
                    // only zag-zag mode need to rotate once,
                    if (!root->right)
                        break;
                }
                /* Link to L Tree */
                LeftTreeMax->right = root;
                LeftTreeMax = LeftTreeMax->right;
                root = root->right;
                LeftTreeMax->right = NULL;
            }
            else
                break;
        }
        /* assemble L Tree, Middle Tree and R tree */
        LeftTreeMax->right = root->left;
        RightTreeMin->left = root->right;
        root->left = header.right;
        root->right = header.left;
        return root;
    }

    splay* New_Node(int data)
    {
        splay* p_node = new splay;
        if (!p_node)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        p_node->data = data;
        p_node->left = p_node->right = NULL;
        return p_node;
    }

    splay* Insert(int data, splay* root)
    {
        static splay* p_node = NULL;
        if (!p_node)
            p_node = New_Node(data);
        else
            p_node->data = data;
        if (!root)
        {
            root = p_node;
            p_node = NULL;
            return root;
        }
        root = Splay(data, root);
        /* This is BST that, all datas <= root->data is in root->left, all datas >
        root->data is in root->right. */
        if (data < root->data)
        {
            p_node->left = root->left;
            p_node->right = root;
            root->left = NULL;
            root = p_node;
        }
        else if (data > root->data)
        {
            p_node->right = root->right;
            p_node->left = root;
            root->right = NULL;
            root = p_node;
        }
        else
            return root;
        p_node = NULL;
        return root;
    }

    splay* Delete(int data, splay* root)
    {
        splay* temp;
        if (!root)
            return NULL;
        root = Splay(data, root);
        if (data != root->data)
            return root;
        else
        {
            if (!root->left)
            {
                temp = root;
                root = root->right;
            }
            else
            {
                temp = root;
                /*Note: Since data == root->data,
                so after Splay(data, root->left),
                the tree we get will have no right child tree.*/
                root = Splay(data, root->left);
                root->right = temp->right;
            }
            free(temp);
            return root;
        }
    }

    splay* Search(int data, splay* root)
    {
        return Splay(data, root);
    }

    void InOrder(splay* root)
    {
        if (root)
        {
            InOrder(root->left);
            cout << "data: " << root->data;
            if (root->left)
                cout << " | left child: " << root->left->data;
            if (root->right)
                cout << " | right child: " << root->right->data;
            cout << "\n";
            InOrder(root->right);
        }
    }
};

void add_node(splay** t_root, splay** current) {

if(*t_root==NULL) {
    *t_root = *current;
    return;
}
if((*current)->data < (*t_root)->data) {
    if((*t_root)->left==NULL) {
        (*t_root)->left = (*current);
    } else {
    add_node(&((*t_root)->left),current);
    }
} else {
    if((*t_root)->right==NULL) {
        (*t_root)->right = *current;
    } else {
        add_node(&((*t_root)->right),current);
    }
}
}

void accept_tree(){
int n;
SplayTree st;
cout<<"\nCREATING BST: (enter 0 to finish)\n";
while(1) {
fflush(stdin);
cout<<"\nEnter node value: ";
cin>>n;
if(n==0) {
break;
}

root =st.Insert(n,root);
}
root = st.Delete(4, root);
}

void inorder(splay* root) {
if(root!=NULL) {
inorder(root->left);
cout<<root->data;
inorder(root->right);
}
}

void preorder(splay* root) {
if(root!=NULL) {
cout<<root->data;
preorder(root->left);
preorder(root->right);
}
}

void postorder(splay* root) {
if(root!=NULL) {
postorder(root->left);
postorder(root->right);
cout<<root->data;
}
}
void drawCircle(float segments, float radius, float sx, float sy)
{
float theta = 2 * 3.1415926 / segments;
float tan_factor = tanf(theta);
float radial_factor = cosf(theta);
float x = radius;
float y = 0;

int cache_pt = 0;
double cache_x;
double cache_y;

glBegin(GL_LINES);
for (int ii = 0; ii < segments; ii++) {
if(!cache_pt) {
cache_x = x+sx;
cache_y = y+sy;
cache_pt = 1;
} else {
//glVertex2f(cache_x,cache_y);
glVertex2f(x + sx, y + sy);
cache_x = x+sx;
cache_y = y+sy;
}
float tx = -y;
float ty = x;
x += tx * tan_factor;
y += ty * tan_factor;
x *= radial_factor;
y *= radial_factor;
}
glEnd();
}
void draw_line(float x1,float y1,float x2, float y2) {
glBegin(GL_LINES);
glVertex2f(x1,y1);
glVertex2f(x2,y2);
glEnd();
}
void draw_text(char* text,float x, float y) {
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
glRasterPos3f(x, y, 0);
for (int i = 0; text[i] != '\0'; i++){
glutBitmapCharacter(font_style, text[i]);
}
}
void drawNode(splay* t_root,float x1,float y1,int level) {
if (t_root==NULL) {
return;
}
float segments = 25;
float radius = 1.0;
float left_angle = 245;
float right_angle = 115;
float branch_length = 12 - level*2.5;
float angle_change = 20;

// Draw the current circle

drawCircle(segments,radius,x1,y1);

char buff[5];
itoa(t_root->data,buff,10);
draw_text(buff,x1,y1);

if(t_root->left) {
// Draw the Left circle
float angle = left_angle - level*angle_change;
double radian = angle*3.14/180;
float m = (double)tan((double)radian);
float x2 = x1 + branch_length * sin((double) radian);
float y2 = y1 + branch_length * cos((double) radian);
drawNode(t_root->left,x2,y2,level+1);
draw_line(x1,y1,x2,y2);
}
if(t_root->right) {
// Draw the Right circle
float angle = right_angle + level*angle_change;
float radian = angle*3.14/180;
float m = (double)tan((double)radian);
float x2 = x1 + branch_length * sin((double) radian);
float y2 = y1 + branch_length * cos((double) radian);
drawNode(t_root->right,x2,y2,level+1);
draw_line(x1,y1,x2,y2);
}
}
void display(void) {
glClearColor (0.0,0.0,0.0,1.0);
glClear (GL_COLOR_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0,10,-30);
glColor3f(1,1,1);
drawNode(root,0,0,0);
glutSwapBuffers();
}
void reshape (int w, int h) {
glViewport (0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
glMatrixMode (GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 27:
exit(0);
break;
}
}
int main (int argc, char **argv) {
accept_tree();
inorder(root);

// OPENGL Drawing functions
glutInit (&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE);
glutInitWindowSize (1200, 800);
glutInitWindowPosition (0, 0);
glutCreateWindow ("A splay tree");

// Register function pointers to the drawing framework
glutDisplayFunc (display);
glutIdleFunc (display);
glutReshapeFunc (reshape);
glutKeyboardFunc (keyboard);
glutMainLoop ();
return 0;
}
