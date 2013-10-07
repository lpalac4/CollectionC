/**
* String Data Structure using C Structs
* @author Luis Palacios
*/


struct String {
  struct String *left,*right;
  int len;  
  char *str; 
};

struct String *string_new(char *str) {
  struct String* newString = (struct String*) malloc(sizeof(struct String));
  newString->len = strlen(str);
  newString->str = (char*) malloc(newString->len+1);
  strcpy(newString->str, str);
  return newString;
}

struct String *string_new_nocopy(char* str) {
  struct String* newString = (struct String*) malloc(sizeof(struct String));
	if(str)
		newString->len = strlen(str);
  newString->str = str;
  return newString;
}

struct String *string_clone(struct String* s) {
  struct String* newString = (struct String*) malloc(sizeof(struct String));
  newString->len = strlen(s->str);
  newString->str = (char*) malloc(newString->len+1);
  strcpy(newString->str, s->str);
  return newString;
}

void string_free(struct String* s) {
  if(s->left) string_free(s->left);
  if(s->right) string_free(s->right);

	if(s->str)
		free(s->str);

  free(s);
}

int string_length(struct String *s) {
  return s->len;
}

/**
* Appends a passed char* onto the struct String 
*/
void string_append(struct String* s, char *b) {
  
  if(s->str) {
		struct String *lstr = string_new_nocopy(s->str);
		s->str = 0;
		s->left = lstr;
    		struct String *rstr = string_new(b);  
		s->right = rstr;
	}
  
  else {
		struct String *lstr = string_new_nocopy(0);
		lstr->left = s->left;
		lstr->right = s->right;
		lstr->len = s->len;
		s->left = lstr;
    		
		struct String *rstr = string_new(b);  
		s->right=rstr;

	}

  s->len = s->left->len + s->right->len;  
}

char string_At(struct String* s, int index) {
  if(s->str) 
    return s->str[index];
	
	if(index < s->left->len)
		return string_At(s->left, index);
	else
		return string_At(s->right, index-s->left->len);		
}

int min(int a, int b){
	if(a<b)
		return a;
	else 
		return b;
}

int string_range_helper(struct String* s, int start, int length, char *out) {
	if(s->str) {
		memcpy(out,&s->str[start],min(s->len-start,length));
		return min(s->len-start,length);
	}
	else {
		int leftlen = s->left->len;
		if(start<leftlen) {
			int leftbytes = string_range_helper(s->left,start,length,out);
			if(start+length>leftlen) 
				leftbytes+=string_range_helper(s->right,0,length-leftbytes,out+leftbytes);			
			return leftbytes;
		}
		else {
			return string_range_helper(s->right,start-leftlen,length,out);
		}
	}
}

char* string_range(struct String* s, int start, int length) {
  char *substr = (char*) malloc(length+1);
  
  string_range_helper(s,start,length,substr);
  substr[length]=0; // null terminator
  return substr;
}

char* string_chars(struct String* s) {
  return string_range(s,0,s->len);
}


