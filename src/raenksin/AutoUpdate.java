package raenksin;

import raenksin.frames.UpdateMainFrame;
import utils.ListUtil;
import utils.MD5Util;

import javax.swing.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

public class AutoUpdate {

    public static void main(String[] args){
        UpdateMainFrame mainFrame = new UpdateMainFrame();

        List<String> md5List = new ArrayList<>();
        List<String> modList = new ArrayList<>();

        String path="D:\\JavaProjects\\RaenksinAutoUpdate\\examples";
        File file = new File(path);
        File[] fs = file.listFiles();
        try{
            for(File f:fs){
                if(!f.isDirectory()){
                    modList.add(f.getName());
                    try {
                        md5List.add(MD5Util.getMd5ByFile(f));
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                    }
                }
            }
        }catch (NullPointerException ex){
            ex.printStackTrace();
        }
        List<String> mixedModList = new ArrayList<>();
        mixedModList = ListUtil.mixModList(md5List,modList);
        System.out.println(mixedModList);
    }

}
