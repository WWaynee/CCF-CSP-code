#include <iostream>
using namespace std;

typedef unsigned char uc;

const int S = 2e6+5;
const int L = 3e6;

uc raw[S];	// 保存解压前的数据，数据范围0~255用unsigned char
uc output[L];	// 保存解压后的数据
int tot = 0;

int cnt = 0; // 计算是否输出了8个字节

int hex2int(char ch) {
	if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
	else return ch - '0';
}

// 小端方式字节串转换成int	
int bytes2int(int begin, int end) {
	long ans = 0;
	int mul = 1;
	for (int i = begin; i <= end; i++) {
		ans += raw[i] * mul;
		mul *= 128;
	}
	return ans;
}

// 1个字节打印成2个hex
void printhex(uc ch) {
	cnt++;
	int post = ch & 15;
	int pre = (ch >> 4) & 15;
	if (pre >= 10) cout<<(char)(post - 10 + 'a');
	else cout<<pre;
	if (post >= 10) cout<<(char)(post - 10 + 'a');
	else cout<<post;
	if (cnt == 8) {
		cout<<endl;
		cnt = 0;
	}
}

// 将元素首字节最后2位转为int
int last2bit(uc ch) {
	uc res = ch << 6;
	res = res >> 6;
	return res;
}

int main() {
	int s; // 字节数，待解压缩数据范围是[0, s-1]
	cin>>s;
	char cur, pre;
	for (int i = 0; i < 2*s; i++) {
		cin>>cur;
		if (i & 1) {	// 每2个字符转换成一个字节
			raw[i/2] = (hex2int(pre) * 16 + hex2int(cur));
		} else {
			pre = cur;
		}
	}
	// 引导域解析，引导域范围是[0, offset]，解压缩后数据长度为data_len
	int offset = 0;
	for (; raw[offset] >> 7 ; offset++);
	int data_len = 0, mul = 1;
	for (int i = 0; i < offset; i++) {
		data_len += (raw[i] - 128) * mul;
		mul *= 128;
	}
	data_len += raw[offset] * mul;
	offset++;
	// 元素解析
	while (offset < s) {
		// 1. 首字节最低2位是00：字面量
		if (last2bit(raw[offset]) == 0) {
			int p_len = (raw[offset] >> 2) + 1;
			if (p_len <= 60) {
				// 1.1 l<=60，首字节最高6个bit表示(l-1)
				for (int i = 0; i < p_len; i++) {
					printhex(raw[++offset]);
					output[tot++] = raw[offset];
				}
				offset++; // 进入下一个元素的首字节
			} else {	// 1.2 l>60，首字节最高6个bit减去59
				int post_len = p_len - 60;	// 随后的post_len个字节小端方式存储长度
				offset++;
				int len_len = bytes2int(offset, offset + post_len - 1) + 1;
				offset += post_len; // 进入需要打印的字面量的第一个字符
				for (int i = 0; i < len_len; i++) {
					printhex(raw[offset++]);	// 会在最后自增到下一个元素的首字节
					output[tot++] = raw[offset];
				}
			}
		}
		// 首字节最低两位是01：回溯引用
		else if (last2bit(raw[offset]) == 1) {
			// 解析o和l
			int post8bit = bytes2int(offset + 1, offset + 1);
			int pre3bit = bytes2int(offset, offset) >> 5;
			int o = post8bit + pre3bit * 256;
			raw[offset] = raw[offset] << 3;
			raw[offset] = raw[offset] >> 5;
			int l = raw[offset] + 4;
			// 回溯操作
			if (o >= l) {
				int end = tot - o + l;
				for (int i = tot - o; i < end; i++) {
					printhex(output[i]);
					output[tot++] = output[i];
				}
			} else {
				int print_len = 0, begin = tot - o - 1, end = tot - 2;
				int i = begin;
				while (print_len < l) {
					printhex(output[i]);
					output[tot++] = output[i++];
					if (i > end) {
						i = begin;
					}
					print_len++;
				}
			}
			offset += 2;	// 跳转到下一个元素的首字节
		}
		// 首字节最低两位是10：回溯引用
		else if (last2bit(raw[offset]) == 2) {
			int o = bytes2int(offset + 1, offset + 2);
			raw[offset] = raw[offset] >> 2;
			int l = raw[offset] + 1;
			//	回溯操作
			if (o >= l) {
				int end = tot - o + l;
				for (int i = tot - o; i < end; i++) {
					printhex(output[i]);
					output[tot++] = output[i];
				}
			} else {
				int print_len = 0, begin = tot - o - 1, end = tot - 2;
				int i = begin;
				while (print_len < l) {
					printhex(output[i]);
					output[tot++] = output[i++];
					if (i > end) {
						i = begin;
					}
					print_len++;
				}
			}
			offset += 3;	// 跳转到下一个元素的首字节
		}
		// 首字节最低两位是11，非法，因为数据一定合法所以可以不处理
	}
	return 0;
}