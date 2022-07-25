///=====================================================================
//�ļ����ƣ� NumToStr.h�ļ�
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��
//��20200916�����Σ�ʵ�ֶ�������ת��Ϊ�ַ��������صĹ���
//��20200918�����ˣ�����͹淶NumToStr.h��NumToStr.c�ļ�
//��ֲ���򣺡��̶���
//=====================================================================
#include "NumToStr.h"
char str[MAX_SIZE];//�洢ת������ַ���


//======================================================================
//�������ƣ�return_char
//���ܸ�Ҫ����ת������ַ������ַ�����
//����˵����data:���ݣ������һ�ֽ�����    
//�������أ���
//======================================================================
void return_char(char data) {
	int i = 0;
	i = strlen(str);
	str[i] = data;
}
//======================================================================
//�������ƣ�NumStr_putc
//���ܸ�Ҫ�������鷵��һ���ַ�
//����˵����c:���ݣ�����������һ�ֽ����ݵ�ASCIIֵ
//�������أ���
//======================================================================
static void NumStr_putc(int c, int *count, NUM_STR *info)
{
	
	
	switch (info->dest) {
	case DEST_CONSOLE:
		info->func((char)c);
		break;
	case DEST_STRING:
		*(info->loc) = (unsigned char)c;
		++(info->loc);
		break;
	default:
		break;
	}
	*count += 1;
}
//======================================================================
//�������ƣ�NumStr_mkfloatstr
//���ܸ�Ҫ����������ת��Ϊ�ַ���
//����˵���� *f:���������ݣ�float������
//       c[]:�ַ������飺ת����ĵ����ַ�������
//�������أ���
//======================================================================
int NumStr_mkfloatstr(double* f, char c[], int precision_width)
{
                uint32_t p,i,j,k,a[5]={0},b[19]={0};
	uint64_t q;
	double tempf;
	int zeroNum=precision_width;   //��20201119��-1/3
	p=0;
	q=0;
	//float m;
	double m;
	p=(uint32_t)*f;     //��������
	tempf=(*f-p);
	if(precision_width==0)
	               q=(*f-p)*100000000000000000;    //С������
	else
	{
		while(precision_width--)    
		tempf*=10;
		q=tempf;
	}
	m=*f-p;
	k=0;
	while(m<1&&m!=0)    //��20201119��-2/3   ԭΪwhile(m<1)
	{
		m=m*10;
		k++;
	};
	k--;          //��¼С����󵽵�һλ��Ϊ���С��֮ǰ �ж��ٸ�0.

		i=0;
	if(0==p)//��������Ϊ0
		c[i++]='0';
	else//�������ֲ�Ϊ0
	{
		j=0;
		while(p!=0)//���������
		{
			a[j++]=p%10;
			p/=10;
		}
		while(j>0)//����������תΪ���򣬲�ת��Ϊ��Ӧ���ַ���ʽ
		{
			c[i++]=a[j-1]+'0';
			--j;
		}
	}
	c[i++]='.';   //С����
	if(0==q)     //С������Ϊ0
		while(zeroNum--) c[i++]='0';     //��20201119��-3/3   ԭΪc[i++] = '0';
	else    //С�����ֲ�Ϊ0
	{
		j=0;

		while(q!=0)//���������
		{
			b[j++]=q%10;
			q/=10;
		}
		while(k!=0)
		{
			b[j++]=0;
			k--;
		}
		while(j>0)//����������תΪ���򣬲�ת��Ϊ��Ӧ���ַ���ʽ
		{
			c[i++]=b[j-1]+'0';
			--j;
		}
	}
	c[i]='\0';
	return i;
              
}
//======================================================================
//�������ƣ�NumStr_mknumstr
//���ܸ�Ҫ������������ת��Ϊ�ַ���������numstr��
//����˵����numstr:�ַ����׵�ַ�����ڽ���ת��Ϊ�ַ�������������
//       nump:�޷����������ݣ���ת��Ϊ���ε����ݴ��뺯��
//       neg:���޷���:�ж�����ʱ�з��Ż����޷�������
//       radix:��ʽѡ��:ȷ�������ʽ���磺ʮ���ƻ�ʮ������...
//�������أ���
//======================================================================
static int NumStr_mknumstr(char *numstr, void *nump, int neg, int radix)
{
	int a, b, c;
	unsigned int ua, ub, uc;

	int nlen;
	char *nstrp;

	nlen = 0;
	nstrp = numstr;
	*nstrp++ = '\0';

	if (neg) {
		a = *(int *) nump;
		if (a == 0) {
			*nstrp = '0';
			++nlen;
			goto done;
		}
		while (a != 0) {
			b = (int) a / (int) radix;
			c = (int) a - ((int) b * (int) radix);
			if (c < 0) {
				c = ~c + 1 + '0';
			} else {
				c = c + '0';
			}
			a = b;
			*nstrp++ = (char) c;
			++nlen;
		}
	} else {
		ua = *(unsigned int *) nump;
		if (ua == 0) {
			*nstrp = '0';
			++nlen;
			goto done;
		}
		while (ua != 0) {
			ub = (unsigned int) ua / (unsigned int) radix;
			uc = (unsigned int) ua - ((unsigned int) ub * (unsigned int) radix);
			if (uc < 10) {
				uc = uc + '0';
			} else {
				uc = uc - 10 + 'A';
			}
			ua = ub;
			*nstrp++ = (char) uc;
			++nlen;
		}
	}
	done: return nlen;
}
/********************************************************************/
static void NumStr_pad_zero(int curlen, int field_width, int *count,
		NUM_STR *info) {
	int i;

	for (i = curlen; i < field_width; i++) {
		NumStr_putc('0', count, info);
	}
}

/********************************************************************/
static void NumStr_pad_space(int curlen, int field_width, int *count,
		NUM_STR *info) {
	int i;

	for (i = curlen; i < field_width; i++) {
		NumStr_putc(' ', count, info);
	}
}
//======================================================================
//�������ƣ�NumStr
//���ܸ�Ҫ�����ݽ��յĲ�����Ϣ�����ݽ���ת�����
//����˵����info:�����ַ�������Ϣ
//       fmt:�����ʽ��Ϣ
//       ap:va_listָ��ָ���ʽ��Ϣ���
//�������أ���
//======================================================================
int NumStr(NUM_STR *info, const char *fmt, char * ap)
{
//	#pragma anon_unions
	/*union ftooc
	{
		double a1;
		struct{
			int c1;
			int c2;
		};
		struct{
			char b1;
			char b2;
			char b3;
			char b4;
			char b5;
			char b6;
			char b7;
			char b8;
		}tempc;

	}un1;*/
	char *p;
	int c;
	//char temp1;
	char vstr[33]={'0'};
	char *vstrp;
	int vlen;

	int done;
	int count;

	int flags_used;
	int field_width;
	int length_modifier;
	int precision_used;
	int precision_width;
	int ival;                  //����������������
	double fval;                //�������ո�������
	int schar, dschar;
	int *ivalp;
	char *sval;
	int cval;
	unsigned int uval;

	count = 0;
	length_modifier=0;
	precision_used=TRUE;
	//�Ӹ�ʽ�ַ�����һ���ַ���ʼ��ʽ���������
	for (p = (char *) fmt; (c = *p) != 0; p++)
	{
		//��ȡ%ǰ����ַ���ֱ��������ַ�������\n���ת���ַ�
		if (c != '%')
		{
#ifndef UNIX_DEBUG
			//%֮ǰ���ַ�
			if (c != '\n') {
				NumStr_putc(c, &count, info);
			}
			//������з�
			else {
				NumStr_putc(0x0D /* CR */, &count, info);
				NumStr_putc(0x0A /* LF */, &count, info);
			}
#else
			NumStr_putc(c, &count, info);
#endif

			continue;
		}


		//��ʱ�ַ�Ϊ%  �鿴�ٷֺź�ĵ�һ����ʽ�ַ����������ʽ�ַ���������Ӧ����ж�
		//�����Ӧ���޸ı�־
		flags_used = 0;
		done = FALSE;
		while (!done) {
			switch (/* c = */*++p) {
			case '-':
				flags_used |= FLAGS_MINUS;
				break;
			case '+':
				flags_used |= FLAGS_PLUS;
				break;
			case ' ':
				flags_used |= FLAGS_SPACE;
				break;
			case '0':
				flags_used |= FLAGS_ZERO;
				break;
			case '#':
				flags_used |= FLAGS_POUND;
				break;
			default:
				/* we've gone one char too far */
				--p;
				done = TRUE;
				break;
			}
		}


		//���%������һ���ַ� ȷ���������
		field_width = 0;
		done = FALSE;
		while (!done) {
			switch (c = *++p) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				field_width = (field_width * 10) + (c - '0');
				break;
			default:
				/* we've gone one char too far */
				--p;
				done = TRUE;
				break;
			}
		}
		//��ʱ�ַ�Ϊ%���Ƿ���.����
		if (/* (c = *++p) */*++p == '.') {
			/* precision_used = TRUE; */

			/*
			 * Must get precision field width, if present.
			 */
			precision_width = 0;
			done = FALSE;
			while (!done) {
				switch ( c = *++p) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
#if 1
				precision_width = (precision_width * 10) +	(c - '0');

#endif
					break;
				default:
					/* we've gone one char too far */
					--p;
					done = TRUE;
					break;
				}
			}
		} else {
			/* we've gone one char too far */
			--p;
#if 1
			precision_used = FALSE;
			precision_width = 0;
#endif
		}
		//�ж� ������Ƿ���lf��LF��
		switch (/* c = */*++p) {
		case 'h':
			// length_modifier |= LENMOD_h;
			break;
		case 'l':
			 length_modifier |= LENMOD_l;
			break;
		case 'L':
			 length_modifier |= LENMOD_L;
			break;
		default:
			/* we've gone one char too far */
			--p;
			break;
		}

		//pΪ��ʽ�ַ������׵�ַ
		switch (c = *++p) {
		case 'd':
		case 'i':
			 //��ʱapΪָ��ɱ�����б�ĵ�һ������
			ival = (int) va_arg(ap, int);  //���ص�ǰ����������apָ����һ������
			vlen = NumStr_mknumstr(vstr, &ival, TRUE, 10);//������ת�����ַ��ͱ�����vstr�У������ַ���vlen
			vstrp = &vstr[vlen];  //ָ��ת��������һ���ַ�

			//������С��0�����'-'�ţ������ַ����ȼ�1
			if (ival < 0) {
				schar = '-';
				++vlen;
			}
			//��������С��0����ӡ�+���Ż��ߡ� ������Ϊ0�������ַ����ȼ�1
			else {
				if (IS_FLAG_PLUS(flags_used)) {
					schar = '+';
					++vlen;
				} else {
					if (IS_FLAG_SPACE(flags_used)) {
						schar = ' ';
						++vlen;
					} else {
						schar = 0;
					}
				}
			}
			dschar = FALSE;

			/*
			 * do the ZERO pad.
			 */
			if (IS_FLAG_ZERO(flags_used)) {
				if (schar)
					NumStr_putc(schar, &count, info);  //�������
				dschar = TRUE;
				NumStr_pad_zero(vlen, field_width, &count, info);
				vlen = field_width;
			} else {
				if (!IS_FLAG_MINUS(flags_used)) {
					NumStr_pad_space(vlen, field_width, &count, info);  //����ո�

					if (schar)
						NumStr_putc(schar, &count, info);
					dschar = TRUE;
				}
			}

			/* the string was built in reverse order, now display in */
			/* correct order */
			if (!dschar && schar) {
				NumStr_putc(schar, &count, info);
			}
			goto cont_xd;  //��ʼ��ת

		//------------------�˴���Ӹ������������---------------------------------------
		case 'f':
			//���������ݱ����� double�ʹ�����Ϸ�ʽ���£�
			//3.140001 ��Ӧ������:0x0x4048F5C3��
			//3.140001 ��double��:0x40091EB85F577E6C
			//ʵ�ʴ������� ������ ��������Ϊ:0x6000000040091EB8 ʵ���ǽ���ת��Ϊdouble������
			//����˳���ˣ�����Ҫ�����ǽ������ֽ���ǰ��Ȼ���0x60�Ƶ�������ǰ�ĸ��ֽں��λ�á�
			//��20200816��  XSX��������������Ż�����
            
           
			ap = ap +4; //�����ַ��������У������Ż��ᵼ�³���
			fval = (double)va_arg(ap, double);
		
			//��20200816��  XSX����������ĸ������������
			//������С��0�����'-'�ţ������ַ����ȼ�1
			if (fval < 0) {
				schar = '-';
				fval = -fval;				//����ȡ��������
				++vlen;
			}
			//��������С��0����ӡ�+���Ż��ߡ� ������Ϊ0�������ַ����ȼ�1
			else {
				if (IS_FLAG_PLUS(flags_used)) {
					schar = '+';
					++vlen;
				}
				else {
					if (IS_FLAG_SPACE(flags_used)) {
						schar = ' ';
						++vlen;
					}
					else {
						schar = 0;
					}
				}
			}
			
			dschar = FALSE;

			//ȷ���Ƿ�ʹ��С���㾫����ֵ
			if (precision_used)
			{
				vlen = NumStr_mkfloatstr(&fval, vstr, precision_width);//��������ת�����ַ��ͱ�����vstr�У������ַ���vlen
				vstrp = &vstr[0];  //ָ��ת����ĵ�һ���ַ�
			}
			else
			{
				if (length_modifier == 0)   //�����;��ȵ�С�����6λ
				{
					vlen = NumStr_mkfloatstr(&fval, vstr, 6);//��������ת�����ַ��ͱ�����vstr�У������ַ���vlen
					vstrp = &vstr[0];  //ָ��ת����ĵ�һ���ַ�
				}
				else
				{
					vlen = NumStr_mkfloatstr(&fval, vstr, 6);//��������ת�����ַ��ͱ�����vstr�У������ַ���vlen
					vstrp = &vstr[0];  //ָ��ת����ĵ�һ���ַ�
				}

			}

			/*
			 * do the ZERO pad.
			 */
			if (IS_FLAG_ZERO(flags_used)) {
				if (schar)
					NumStr_putc(schar, &count, info);  //�������
				dschar = TRUE;
				NumStr_pad_zero(vlen, field_width, &count, info);
				vlen = field_width;
			}
			else {
				if (!IS_FLAG_MINUS(flags_used)) {
					NumStr_pad_space(vlen, field_width, &count, info);  //����ո�

					if (schar)
						NumStr_putc(schar, &count, info);
					dschar = TRUE;
				}
			}

			/* the string was built in reverse order, now display in */
			/* correct order */
			if (!dschar && schar) {
				NumStr_putc(schar, &count, info);
			}
			while (*vstrp)
				NumStr_putc(*vstrp++, &count, info);
			if (IS_FLAG_MINUS(flags_used)) {
				NumStr_pad_space(vlen, field_width, &count, info);
			}
			break;
        //������16�����������
		case 'x':
		case 'X':
			uval = (unsigned int) va_arg(ap, unsigned int);
			vlen = NumStr_mknumstr(vstr, &uval, FALSE, 16);
			vstrp = &vstr[vlen];

			dschar = FALSE;
			if (IS_FLAG_ZERO(flags_used)) {
				if (IS_FLAG_POUND(flags_used)) {
					NumStr_putc('0', &count, info);
					NumStr_putc('x', &count, info);
					/*vlen += 2;*/
					dschar = TRUE;
				}
				NumStr_pad_zero(vlen, field_width, &count, info);
				vlen = field_width;
			} else {
				if (!IS_FLAG_MINUS(flags_used)) {
					if (IS_FLAG_POUND(flags_used)) {
						vlen += 2;
					}
					NumStr_pad_space(vlen, field_width, &count, info);
					if (IS_FLAG_POUND(flags_used)) {
						NumStr_putc('0', &count, info);
						NumStr_putc('x', &count, info);
						dschar = TRUE;
					}
				}
			}

			if ((IS_FLAG_POUND(flags_used)) && !dschar) {
				NumStr_putc('0', &count, info);
				NumStr_putc('x', &count, info);
				vlen += 2;
			}
			goto cont_xd;
		//�޷����԰˽��Ʊ�ʾ���������
		case 'o':
			uval = (unsigned int) va_arg(ap, unsigned int);
			vlen = NumStr_mknumstr(vstr, &uval, FALSE, 8);
			goto cont_u;
		//���������
		case 'b':
			uval = (unsigned int) va_arg(ap, unsigned int);
			vlen = NumStr_mknumstr(vstr, &uval, FALSE, 2);
			goto cont_u;
		//���ָ���ֵ
		case 'p':
			uval = (unsigned int) va_arg(ap, void *);
			vlen = NumStr_mknumstr(vstr, &uval, FALSE, 16);
			goto cont_u;
		case 'u':
			uval = (unsigned int) va_arg(ap, unsigned int);
			vlen = NumStr_mknumstr(vstr, &uval, FALSE, 10);

			cont_u: vstrp = &vstr[vlen];

			if (IS_FLAG_ZERO(flags_used)) {
				NumStr_pad_zero(vlen, field_width, &count, info);
				vlen = field_width;
			} else {
				if (!IS_FLAG_MINUS(flags_used)) {
					NumStr_pad_space(vlen, field_width, &count, info);
				}
			}

			cont_xd: while (*vstrp)
				NumStr_putc(*vstrp--, &count, info);

			if (IS_FLAG_MINUS(flags_used)) {
				NumStr_pad_space(vlen, field_width, &count, info);
			}

			break;
        //�ַ������
		case 'c':
			cval = (char) va_arg(ap, unsigned int);
			NumStr_putc(cval, &count, info);
			break;
		case 's':
			sval = (char *) va_arg(ap, char *);
			if (sval) {
				vlen = strlen(sval);
				if (!IS_FLAG_MINUS(flags_used)) {
					NumStr_pad_space(vlen, field_width, &count, info);
				}
				if(precision_width!=0)
				{
					while (*sval)
					{
						if(precision_width>=1)
						{
							precision_width--;
							NumStr_putc(*sval++, &count, info);
						}
						else {
							break;
						}
					}
				}
				else    //precision_width=0���
				{
					while (*sval)
						NumStr_putc(*sval++, &count, info);
				}
				if (IS_FLAG_MINUS(flags_used)) {
					NumStr_pad_space(vlen, field_width, &count, info);
				}
			}
			break;
		case 'n':
			ivalp = (int *) va_arg(ap, int *);
			*ivalp = count;
			break;

		default:
			NumStr_putc(c, &count, info);
			break;
		}
	}
	return count;
}

//======================================================================
//�������ƣ�NumToStr
//���ܸ�Ҫ����������Ĳ������н���Ȼ������ת�����ַ�������
//����˵����const char *:��ӡ�����ַ�������������ַ������н���������ʽ���
//���磺 value=NumToStr("c=%c\n",c); value�õ���NumToStr(char *)�͵ķ���ֵ��
//       �洢����ת�����ַ�������׵�ַ
//�������أ��ַ����׵�ַ
//======================================================================
char *NumToStr (const char *fmt, ...)
{
	char * ap;
	NUM_STR info;
	memset(str, 0, sizeof(str));//���str�ַ�����
	info.dest = DEST_CONSOLE;  //�궨��Ϊ1
	info.func = &return_char;     //���õĴ����������
	va_start(ap, fmt);  //��ap ���г�ʼ��������ָ��ɱ����������ĵ�һ������
	NumStr(&info, fmt, ap);
	va_end(ap);
	return str;
}

