# MySTL

## Repo Intro

This repo is to try to reconstruct a STL library that include all 6 core parts of STL. This will be done in 5 major steps:

      Step 1, Build Up all containers and data structures.
      
      Step 2, Build Up all algorithms working on one of the data structures selected.
      
      Step 3, Build Up all iterators we need, connect Algorithm and Container together by changing algorithm input from one data structure to one iterator.
      
      Step 4, Include adaptors and functors.
      
      Step 5, Works on memory optimization, include allocators.
      
<i>The Repo is currently at <b>1ST</b> step.</i> 
  
## File structure

all files in root content are testers for some components. Directories are listed below:

    --Containers

      Each file in this directory represents a container, those who start with an "_" should not be called directly from outside of thie directory or be exposed to users.
      
      The containers are listed in a recommended reading sequence:
      
      -- vector.h
      
      -- list.h
            -- _listnode.h 
      
      -- unionFind.h
      
      --PQ.h
      
      -- bintree.h
            -- _binnode.h
      
      -- AVL.h
      -- splay.h
            -- _BST.h
            
      -- graphMatrix.h
            -- graph.h
    
    --Algorithms
    
      Each file in this directory represent an algorithm. Currently the input of those algorithm is one of the data structure we select from /Containers.
      
      The algorithms will be introduced in a recommended reading sequence:
      
      --kSeletion.h

## How to use

    1, Download the repo to local, a star to the repo is appreciated.
    
    2, make sure any C++ compilor is installled in your local env.
    
    3, write a cpp file to call any containers or algorithms at root directory.
    
    4, compile, run.

## More to do

I will implemented the following extra more model and project in very recent time.

[] 234 Tree, RB Tree, Map, Set
[] Strings
[] Dynamic programming

## Special Thanks

This repo has some part referenced from Data Structure and Algorithms course from Tsinghua University(the course is in Chinese), link: 

First Part(http://www.xuetangx.com/courses/course-v1:TsinghuaX+30240184+sp/about)
Second Part(http://www.xuetangx.com/courses/course-v1:TsinghuaX+30240184_2X+sp/about)

Thanks to this great materials.

The repo has also referenced from the book "The annotated STL sources"(STL源码剖析)(https://book.douban.com/subject/1110934/), the book is written in Chinese. Gread book!!!

## Contact Me

Email: nick_fandingwei@outlook.com

Twitter: https://twitter.com/nick_fandingwei

For Chinese user, zhihu is the fastest way to get response from me: https://www.zhihu.com/people/NickWey

You can also check my tech blog for more: http://nickiwei.github.io/

Consider to follow me on Zhihu, Twitter and Github, thanks!
