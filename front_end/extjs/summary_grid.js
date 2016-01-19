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
