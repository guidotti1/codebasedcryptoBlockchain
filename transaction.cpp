#include"transaction.h"

transaction::transaction()
{
	from="";
	to="";
	amount=0;
}

transaction::transaction (string setFrom, string setTo, int setAmount)
{
	from=setFrom;
	to=setTo;
	amount=setAmount;

}

string transaction::getFrom()
{
	return from;
}

string transaction::getTo()
{
	return to;
}

int transaction::getAmount()
{
	return amount;
}


void transaction::setFrom(string s)
{
	from=s;
}

void transaction::setTo(string t)
{
	to=t;
}

void transaction::setAmount(int a)
{
	amount=a;
}
