(function () {
    function iconClickHandler(grid, rowIndex, colIndex) {
        var record = grid.getStore().getAt(rowIndex);
        this.fireEvent('iconClick', rowIndex, colIndex, record);
    }

    /**
     *  Grid Definition
     */
    Ext.define('DataGrid', {
        extend: 'Ext.grid.Panel',
        alias: 'widget.datagrid',

        requires: [
            'DataStore'
        ],

        store: 'DataStore',
        minHeight: 60,
        loadMask: true,

        columns: {
            defaults: { flex: 1, renderer: this.defaultRenderer },
            items: [
                {
                    xtype: 'actioncolumn',
                    width: 150,
                    items: [{
                        icon:'icon1.png',
                        tooltip:'editing',
                        handler: iconClickHandler,
                        style:'margin-left:5px',
                        getClass: function(value,metadata,record){
                            var changeType = record.get('changeType');
                            if (changeType === 'editing') {
                                return 'x-grid-center-icon';
                            } else {
                                return 'x-hide-display';
                            }
                        }
                    }, {
                        icon:'icon2.png',
                        tooltip:'roll back',
                        handler: iconClickHandler,
                        style:'margin-left:5px',
                        getClass: function(value,metadata,record){
                            var changeType = record.get('changeType');
                            if (changeType === 'deleted' || changeType === 'modified') {
                                return 'x-grid-center-icon';
                            } else {
                                return 'x-hide-display';
                            }
                        }
                    }, {
                        icon: 'icon3.png',
                        tooltip:'delete',
                        handler: iconClickHandler,
                        style:'margin-left:5px',
                        getClass: function(value,metadata,record){
                            var changeType = record.get('changeType');
                            if (changeType === 'editable') {
                                return 'x-grid-center-icon';
                            } else {
                                return 'x-hide-display';
                            }
                        }
                    }]
                },
                { dataIndex: 'xDate', text: 'x Date',
                    renderer : function(date){
                        return Ext.Date.format(new Date(date), 'd-M-Y');
                    }
                },
                { dataIndex: 'y', text: 'y' }
            ]
        },

        defaultSorter : [
            {
                property: 'y',
                direction: 'DESC'
            }
        ],

        viewConfig : {
            stripeRows: false,
            getRowClass: function(record) {
                var changeType = record.get('changeType');
                var isNewAdded = record.get('isNewAdded');
                if(isNewAdded === true){
                    return 'grid-newAdded-row';
                } else if(changeType === 'editing'){
                    return 'grid-editing-row';
                } else if(changeType === 'deleted'){
                    return 'grid-deleted-row';
                }
            },
            listeners : {
                refresh : function (dataview) {
                    Ext.each(dataview.panel.columns, function (column) {
                        if (column.autoSizeColumn === true)
                            column.autoSize();
                    })
                }
            }
        }
    });
})();


/**
 *  Edit Panel Definition
 */

var defaultNumberTextFieldSetting = {
    xtype: 'numberfield',
    labelWidth: 80,
    labelAlign: 'right',
    value : '',
    margin: '5 5 5 5',
    decimalPrecision : 15,
    readOnly : true,
    labelStyle: 'font-weight: bold',
    // Remove spinner buttons, and arrow key and mouse wheel listeners
    hideTrigger: true,
    keyNavEnabled: false,
    mouseWheelEnabled: false
};

Ext.define('EditPanel', {
    extend: 'Ext.panel.Panel',
    alias: 'widget.editpanel',
    collapsible: true,
    border: true,
    requires: [
    ],
    title: 'Edit panel',
    header: {
        titlePosition: 0,
        items: [
            {
                xtype: 'button',
                margins: '0 5',
                width: 80,
                text: 'Discard',
                name: 'editPanelDiscardBtn',
                tooltip: 'discard current edit',
                disabled: true
            }, {
                xtype: 'button',
                margins: '0 5',
                width: 80,
                text: 'Apply',
                name: 'editPanelApplyBtn',
                tooltip: 'apply current edit',
                disabled: true
            }
        ]
    },

    layout: 'column',
    items: [
        {
            xtype: 'container',
            defaults: defaultNumberTextFieldSetting,
            columnWidth : 0.5,
            items :[
                { xtype: 'datefield', fieldLabel: 'x Date', format: 'd-M-Y', key: 'xDate', hideTrigger: false },
                {
                    xtype: 'combobox',
                    fieldLabel: 'y',
                    queryMode: 'local',
                    key: 'y',
                    displayField: 'y',
                    valueField: 'y',
                    store:  { fields: ['y'], data : [] },
                    hideTrigger: false
                },
                { fieldLabel: 'z', key: 'z' }
            ]
        }, {
            xtype: 'container',
            defaults: defaultNumberTextFieldSetting,
            columnWidth : 0.5,
            items :[
                { xtype     : 'textareafield', fieldLabel: 'a', key: 'a', hideTrigger: false },
                { fieldLabel: 'b', key: 'b' },
                { fieldLabel: 'c', key: 'c' }
            ]
        }
    ]
});


(function(){
    Ext.define('EditPanelontroller', {
        extend: 'Ext.app.Controller',

        refs: [
            { ref: 'dataGrid', selector: 'datagrid' },
            { ref: 'editPanel', selector: 'editpanel' },
            { ref: 'wholePanelEditBtn', selector: 'wholepanel button[name=wholePanelEditBtn]' },
            { ref: 'wholePanelDiscardBtn', selector: 'wholepanel button[name=wholePanelDiscardBtn]' },
            { ref: 'wholePanelSaveBtn', selector: 'wholepanel button[name=wholePanelSaveBtn]' },
            { ref: 'editPanelDiscardBtn', selector: 'editpanel button[name=editPanelDiscardBtn]' },
            { ref: 'editPanelApplyBtn', selector: 'editpanel button[name=editPanelApplyBtn]' },
            { ref: 'yCombo', selector: 'editpanel combobox[key=y]' }
        ],

        requires: [
        ],

        isEditable : false,
        editingRecord : null,
        eventParam : null,

        init: function() {
            msgBus.on(msgBus.WHOLE_PANEL_LOAD, this.updateWholePanel, this);
            this.control(
                {
                    'wholepanel button[name=EditBtn]': {
                        'click': this.enableEdit
                    },
                    'wholepanel button[name=DiscardBtn]': {
                        'click': this.discardWholeEdit
                    },
                    'wholepanel button[name=SaveBtn]': {
                        'click': this.saveCurrentEdit
                    },
                    'editpanel button[name=editPanelDiscardBtn]': {
                        'click': this.discardCurrentEdit
                    },
                    'editpanel button[name=editPanelApplyBtn]': {
                        'click': this.applyCurrentEdit
                    },
                    'datagrid': {
                        itemdblclick: function (dv, record, item, index, e) {
                            if (this.isEditable && record.data.changeType !== 'deleted') {
                                this.discardCurrentEdit();
                                record.data.changeType = 'editing';
                                this.editingRecord = record;
                                this.loadData2EditPanel(record.data);
                                this.getDataGrid().getView().refresh();
                            }
                        }
                    },
                    'actioncolumn': {
                        iconClick: function (rowIndex, colIndex, record) {
                            var changeType = record.get('changeType');
                            var isNewAdded = record.get('isNewAdded');
                            if (changeType === 'editable') {  // delete record
                                if (isNewAdded === true) {
                                    this.getDataGrid().store.remove(record);
                                } else {
                                    record.data.changeType = 'deleted';
                                }
                            } else if (changeType === 'deleted') {
                                // if marked as deleted, just rollback changeType since there is no way a record could modified first then delete afterward
                                // delete only perform on unmodified record, if modified, icon should be rollback not delete
                                record.data.changeType = 'editable';
                            } else if (changeType === 'modified') {
                                this.rollbackRecord(record);
                            }
                            this.getDataGrid().getView().refresh();
                        }
                    }
                }
            );
        }
    });
})();


(function() {
Ext.define('Mancini.extension.grid.feature.ClickableSummary', {
	extend: 'Ext.grid.feature.Summary',
	alias: ['feature.clickablesummary'],
	
	mixins: {
        observable: 'Ext.util.Observable'
    },
	
	relayedEvents: [
		'summaryclick'
	],
	
	constructor: function(config) {
		var me = this;
		me.addEvents(
			'summaryclick'
		);
		
		me.callParent(arguments);
		me.mixins.observable.constructor.call(me);
	},
	
	init: function(grid) {
		var me = this;
		
		// wire click event to dom cell click           
        grid.on({
            afterrender: function () {
                this.mon(this.el, 'click', me.onSummaryCellClick, me, { delegate: '.x-grid-cell' });
            }                
        });
		
        grid.relayEvents(me, me.relayedEvents);        
        me.callParent(arguments); 
	},
	
	onSummaryCellClick: function (e, target) {            
        var me = this,
            cell = Ext.get(target),
            row = cell.up(me.summaryRowSelector);
        
        // only execute if this was inside summary row
        // as mentioned in init, there may be a cleaner way to implement this
        if (row) {                
            var grid = Ext.getCmp(cell.up('.x-grid').id),
                column = grid.columns[cell.dom.cellIndex],
                record = me.summaryRecord,
				cellIndex = cell.dom.cellIndex,
				rowIndex = -1;				
            
            me.fireEvent('summaryclick', me, cell, cellIndex, record, row, rowIndex, e);
        }
    },          
	
	renderTFoot: function(values, out) {
        var view = values.view,
            me = view.findFeature('clickablesummary');

        if (me.showSummaryRow) {
            out.push('<tfoot>');
            me.outputSummaryRecord(me.createSummaryRecord(view), values, out);
            out.push('</tfoot>');
        }
    }	
});

Ext.define('TestApp.view.Home', {
	extend: 'Ext.grid.Panel',
	alias: 'widget.home',	
	store: Ext.create('Ext.data.Store', {
		fields: ['first', 'last'],
		data: [
			{ first: 'Bill', last: 'Clay' },
			{ first: 'Tom', last: 'Collins' },
			{ first: 'Joe', last: 'Anderson' }
		]
	}),
	columns: [
		{ text: 'First', dataIndex: 'first', summaryRenderer: function(value, summaryData, dataIndex) {
            return "<a href='#'><span class='midas-summary-cell'>"+value+"<span></a>";
            }
		},
		{ text: 'Last', dataIndex: 'last', summaryType: 'sum', summaryRenderer: function() { return 'last'; } }
	],	
	features: [{		
		ftype: 'clickablesummary',
		dock: 'bottom'
	}]	
});

Ext.define('TestApp.controller.Home', {
	extend: 'Ext.app.Controller',		
	views: ['Home'],
	init: function() {
		var me = this;		
		this.control({
			'viewport > home': {
				summaryclick: function (summar, cell, colIdx, record, row) {
					alert('Clicked cell ' + colIdx);
				}
			}
		});			
	}		
});

Ext.application({
	name: 'TestApp',
	controllers: ['Home'],
	launch: function() {
        Ext.create('Ext.container.Viewport', {
            layout: 'fit',
            items: {
                xtype: 'home'
            }
        });
    }
});

}());
