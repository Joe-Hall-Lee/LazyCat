int BF1(char S[], char T[])
{
	int i = 0;
	int j = 0;
	while (S[i] != '\0' && T[j] != '\0')
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (T[j] == '\0')
		return (i - j);
	else
		return -1;
}


int BF2(char S[], char T[])
{
	int i = 0;
	int j = 0;
	int start = 0;
	while (S[i] != '\0' && T[j] != '\0')
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			start++;
			i = start;
			j = 0;
		}
	}
	if (T[j] == '\0')
		return start;
	else
		return -1;
}