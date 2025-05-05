#### Add Function if no dma is present 
```c
void addComment(const Comment& comment) {

Comment* temp = new Comment[noOfComments + 1];


for (int i = 0; i < noOfComments; i++) {

temp[i] = comments[i];

}

temp[noOfComments] = comment;

  

delete[] comments;

comments = temp;

noOfComments++;

}
```
here no copy constructor is required and this adds a new comment(object)

#### Add Function if Dma is present
here the function remains same
```c
void createPost(const string& title, const string& content) {

Post* temp = new Post[noOfPosts + 1];

  

for (int i = 0; i < noOfPosts; i++) {

temp[i] = posts[i];

}

// temp[noOfPosts] = Post(title, content);

temp[noOfPosts].setTitle(title);

temp[noOfPosts].setContent(content);

delete[] posts;

posts = temp;

noOfPosts++;

}
```
but a copy constructor and an assignment constructor will be required
#### Copy Constructor
```c
// Copy constructor
    MyClass(const MyClass& other) : size(other.size), name(other.name) {
        // Allocate new memory for the copy
        data = new int[size];
        // Copy the contents of the other object's data
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor called." << endl;
    }

    // Assignment operator
    MyClass& operator=(const MyClass& other) {
        // Check for self-assignment (e.g., obj1 = obj1)
        if (this != &other) {
            // Delete existing memory to avoid memory leaks
            delete[] data;

            // Copy non-pointer members
            size = other.size;
            name = other.name;

            // Allocate new memory for the copy
            data = new int[size];
            // Copy the contents of the other object's data
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        cout << "Assignment operator called." << endl;
        return *this;  // Return the current object
    }

    // Destructor
    ~MyClass() {
        delete[] data;  // Free dynamically allocated memory
        cout << "Destructor called for " << name << "." << endl;
    }
```

```c
// Copy constructor
// Copy constructor
    Post(const Post& other) : title(other.title), content(other.content), noOfComments(other.noOfComments) {
        comments = new Comment[noOfComments];
        for (int i = 0; i < noOfComments; i++) {
            comments[i] = other.comments[i];
        }
    }

    // Assignment operator
    Post& operator=(const Post& other) {
        if (this != &other) {  // Check for self-assignment
            title = other.title;
            content = other.content;
            noOfComments = other.noOfComments;

            // Delete existing comments
            delete[] comments;

            // Deep copy comments
            comments = new Comment[noOfComments];
            for (int i = 0; i < noOfComments; i++) {
                comments[i] = other.comments[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Post() {
        delete[] comments;
    }
```



#### Remove (no dma)
```c
void removeComment(const Comment& comment) {

if (comments == nullptr || noOfComments == 0) {

cout << "No comments to remove." << endl;

return;

}

  

Comment* temp = new Comment[noOfComments - 1];

int tempIndex = 0;

  

for (int i = 0; i < noOfComments; i++) {

if (comments[i].getContent() != comment.getContent()) {

temp[tempIndex] = comments[i];

tempIndex++;

}

}

  

delete[] comments;

comments = temp;

noOfComments--;

  

cout << "Comment removed successfully." << endl;

}
```


