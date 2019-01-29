#include "List.h"



List::List()
{
	Text = new Texture;
}


List::~List()
{
	delete Text;
}

void List::SetNext(List* _next)
{
	Next = _next;
}

List* List::GetNext()
{
	return Next;
}
