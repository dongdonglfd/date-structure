 //创建快慢指针
    int fast = 0;
    int slow = 0;
    //求出字符串长度
    int strLength = strlen(s);
    //遍历字符串
    while(fast < strLength) {
        //将当前slow指向字符改为fast指向字符。fast指针+1
        char letter = s[slow] = s[fast++];
        //若慢指针大于0，且慢指针指向元素等于字符串中前一位元素，删除慢指针指向当前元素
        if(slow > 0 && letter == s[slow - 1])
            slow--;
        else
            slow++;
    }
    //在字符串结束加入字符串结束标志'\0'
    s[slow] = 0;
    return s;
