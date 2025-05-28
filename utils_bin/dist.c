
#include <stdio.h>
#include <time.h>
#include <direct.h>
#include "./tcc/sha1/sha1.h"
#include "../dist.h"


// Makefile call example:
// ./utils_bin/tcc/tcc.exe ./utils_bin/tcc/sha1/sha1.c -run ./compile.c DAY_VER [COMMENT]

// // 项目名
// const char* project = "RLF73009";
// // 默认编译二进制路径
// const char* binary_path = "./_build/RD2208001-RLF73009.hex";
// // 二进制文件后缀
// const char* binary_suffix = "hex";

#define BUFFER_SIZE 4096
#define SHA_DIGEST_LENGTH 20
unsigned char hash[SHA_DIGEST_LENGTH];

void calc_sha1_of(FILE* file);
void copyFile(const char* sourcePath, const char* destinationPath);
int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("parameter should be [day version] ([comment])\n");
		return 1;
	}

	struct tm* local;
	time_t t = time(NULL);
	local = localtime(&t);

	FILE* file = fopen(binary_path, "rb");
	if (file == NULL) {
		printf("Error opening the file [%s].\n", binary_path);
		return 1;
	}
	calc_sha1_of(file);
	fclose(file);

	char dist_path[1024];
	char day_version[9];
	char hash_str[7];
	char comment_str[64];
	sprintf(day_version, "%02d%02d%02d%s",
			local->tm_year - 100,
			local->tm_mon + 1,
			local->tm_mday,
			argv[1]);
	sprintf(hash_str, "%02x%02x%02x",
			hash[0], hash[1], hash[2]);
	if(argc >= 3) {
		sprintf(comment_str, "-%s", argv[2]);
	} else {
		sprintf(comment_str, "");
	}
	sprintf(dist_path, "./dist/%s-%s-[%s]%s.%s",
			project,
			day_version,
			hash_str,
			comment_str,
			binary_suffix);

	mkdir("dist");
	// Copy
	copyFile(binary_path, dist_path);
	// Move
	// rename(binary_path, dist_path);
	printf("Distribute to %s\n", dist_path);
	return 0;
}

void calc_sha1_of(FILE* file) {
	unsigned char buffer[BUFFER_SIZE];
	int bytesRead;
	SHA1_CTX shaContext;
	SHA1Init(&shaContext);

	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) != 0) {
		SHA1Update(&shaContext, buffer, bytesRead);
	}
	SHA1Final(hash, &shaContext);
	printf("SHA-1 hash value: ");
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		printf("%02x", hash[i]);
	}
	printf("\n");
}

void copyFile(const char* sourcePath, const char* destinationPath) {
	FILE* sourceFile = fopen(sourcePath, "rb");
	FILE* destinationFile = fopen(destinationPath, "wb");

	if (sourceFile == NULL || destinationFile == NULL) {
		printf("Error opening files.\n");
		return;
	}

	char buffer[4096];
	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
		fwrite(buffer, 1, bytesRead, destinationFile);
	}

	fclose(sourceFile);
	fclose(destinationFile);
}
