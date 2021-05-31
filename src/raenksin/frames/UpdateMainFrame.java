package raenksin.frames;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

public class UpdateMainFrame extends BasicFrame {
    JTable modListTable;
    JPanel updatePanel;
    DefaultTableModel modTableModel;
    String[] columnName = {"mod编号","mod名称","MD5","执行操作"};
    int columnLength = 4;


    public UpdateMainFrame(){
        super();
        this.setTitle("自动更新");
        this.setSize(1200,800);
        this.setLayout(null);

        modListTable = new JTable();
        modListTable.setLocation(185,100);
        modListTable.setSize(980,600);
        modTableModel = new DefaultTableModel();
        modTableModel.setColumnIdentifiers(columnName);
        modListTable.setModel(modTableModel);
        modListTable.setVisible(true);

        JScrollPane modScrollPane = new JScrollPane(modListTable);
        modScrollPane.setBounds(185,100,980,600);
        modScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        modScrollPane.setBackground(Color.red);
        modScrollPane.setVisible(true);

        updatePanel = new JPanel();
        updatePanel.setLayout(null);
        updatePanel.setBackground(Color.BLACK);
        updatePanel.setLocation(0,0);
        updatePanel.setSize(1200,800);
        updatePanel.add(modScrollPane);
        updatePanel.setVisible(true);
        this.add(updatePanel);

        this.setVisible(true);

    }

    private void updateModTable(List<String> modMixedList){

        for(int i = 0; i < modMixedList.size() / columnLength;i++){
            modTableModel.addRow((Vector<?>) modMixedList);
        }
    }

}
