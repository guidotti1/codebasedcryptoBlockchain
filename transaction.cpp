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