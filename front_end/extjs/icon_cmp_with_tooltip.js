var fs = new Ext.form.FieldSet({
    title: 'query condition',
    collapsible: true,
    layout: 'vbox',
    height: 80,
    defaults: {
        border: false
    },
    items:[
        {
            xtype: 'panel',
            width: '100%',
            flex: 1,
            defaults: {
                labelWidth: 60
            },
            items:[
                {
                    xtype:'combobox',
                    style: 'position:absolute;left:15px;',  //定位
                    name:'s_ownerunit',
                    fieldLabel:'使用单位',
                    width:200
                },
                /**
                 * icon tooltip, it could beside some component
                 */
                {
                    xtype: 'image',
                    src: '../lib/view/resource/something.png',
                    height: 20,
                    width: 20,
                    margin: '5 5 5 5',
                    shrinkWrap: 3,
                    listeners: {
                        afterrender: function(c) {
                            Ext.create('Ext.tip.ToolTip', {
                                target: c.getEl(),
                                html: 'something description placeholder'
                            });
                        }
                    }
                }
            ]
        },
        {
            xtype: 'panel',
            width: '100%',
            flex: 1,
            defaults:{
                labelWidth: 60
            },
            items:[
                {
                    xtype: 'combobox',
                    style: 'position:absolute;left:225px;',
                    name: 's_zgks',
                    fieldLabel:'主管科室',
                    width:150
                },
                {
                    xtype:'checkboxfield',
                    style: 'position:absolute;left:395px;',
                    name:'s_ctjyf',
                    boxLabel:'统计月份',
                    width:80
                }
            ]
        }
    ]
});