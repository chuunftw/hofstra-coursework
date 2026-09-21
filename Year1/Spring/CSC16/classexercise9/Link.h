#ifndef LINK_H
#define LINK_H

typedef int DataType;

class Link
{
        public:
        Link(DataType data = 0, Link *next =0);
        void setData(DataType data)  {this -> data = data; }
        DataType getData() {return data; }

        void setNext(Link *next) {this->next = next; }
        Link *getNext() { return next; }
        private:
        Link *next;
        DataType data;

};


#endif //LINK_H





