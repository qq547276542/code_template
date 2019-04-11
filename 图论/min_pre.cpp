string min_pre(string str){   //原串中为树的dfs路线，0代表进入子树，1代表返回父节点
			vector<string> box;
			string ret = "";
			int equal = 0, st = 0;
			for(int i = 0; i < str.size(); i++){
					 if(str[i] == '0') equal++;
					 else equal--;
					 if(equal == 0){
								if(i - 1 > st + 1){
										box.push_back("0" + min_pre(str.substr(st + 1,i - 1 - st)) + "1");
								}else box.push_back("01");
								st = i + 1;
					 }
			}
			sort(box.begin(), box.end());
			for(int i = 0; i < box.size(); i++) ret += box[i];
			return ret;
}
