package utils;

import java.util.ArrayList;
import java.util.List;

public class ListUtil {
    public static List<String> mixModList(List<String> md5List, List<String> modList){
        List<String> mixModList = new ArrayList<>();
        for(int i = 0;i < md5List.size();i++){
            mixModList.add(String.valueOf(i));
            mixModList.add(modList.get(i));
            mixModList.add(md5List.get(i));
            mixModList.add("null");
        }
        return mixModList;
    }
}
