Ext.ns('midas.msgbus');
// simulate a message bus
midas.msgbus.MsgBus = new Ext.util.Observable();

/**
 * Usage:
 * 1. add one custom even name in this file like:
 *      midas.msgbus.MsgBus.addEvents('message');
 * 2. The event publisher can publish event like this:
 *      midas.msgbus.MsgBus.fireEvent('message', values);
 * 3. Any component who wants to subscribe this event, can handle it like this:
 *      midas.msgbus.MsgBus.on('message', function(){...}, this);
 */
(function(){
    var msgBus = midas.msgbus.MsgBus;

    msgBus.PANEL_LOAD = 'panel.load';

    msgBus.addEvents(msgBus.PANEL_LOAD);
})();





/**
 * Utilities class, which contains some common functions
 */
Ext.require([
    'midas.msgbus.MsgBus'
], function(){
    var msgBus = midas.msgbus.MsgBus;

    /**
     * check a variable is N/A
     * @param number
     * @returns {boolean}
     */
    var isNA = function(number){
        if( (number === null) || (number === undefined ) || isNaN(number) || (!isFinite(number)) || number === ''){
            return true;
        } else {
            return false;
        }
    };

    midas.MidasUtils =  {
        singleton: true,
        recordState : {
            readonly : 'readonly',
            editable : 'editable',
            editing : 'editing',
            deleted : 'deleted',
            modified : 'modified'
        },

        /**
         * format number to date
         * @param number
         * @returns {string}
         */
        numberToDate : function(number) {
            if( isNA(number) ){
                return '-';
            }

            return Ext.Date.format(new Date(number), 'd-M-Y h:m');
        },

        /**
         * format number to percentage
         * @param number
         * @returns {string}
         */
        numberToPercentage : function(number) {
            if( isNA(number) ){
                return '-';
            }

            return ((number*100).toFixed(1) + "%");
        },

        /**
         * format big double number to million unit
         * @param number
         * @returns {*}
         */
        bigDoubleFormat : function(number) {
            if( isNA(number) ){
                return '-';
            }

            return Ext.util.Format.number(number/ 1000000, '0,000.0');
        },

        /**
         * format big double number to grouped monetary format
         * @param number
         * @returns {*}
         */
        bigDoubleHoverFormat : function(number) {
            if( isNA(number) ){
                return '-';
            }

            return Ext.util.Format.number(number, '0,000');
        },

        /**
         * format small double number, keep one digits precision
         * @param number
         * @returns {*}
         */
        smallDoubleFormat : function(number) {
            if( isNA(number) ){
                return '-';
            }
            return Ext.util.Format.number(number, '0.0');
        },

        /**
         * convert string to uppercase
         * @param str
         * @returns {*}
         */
        toUpperCase : function(str){
            if(str !== null && str !== undefined && typeof str === "string"){
                return str.toUpperCase();
            }else{
                return '';
            }
        },

        /**
         * A default Renderer for all columns
         * @param value -- The data value for the current cell
         * @param metaData -- A collection of metadata about the current cell
         * @see http://docs.sencha.com/extjs/4.2.2/source/Column3.html#Ext-grid-column-Column-cfg-renderer
         * @returns {*|string}
         */
        defaultRenderer: function (value, metaData) {
            if(value && metaData){
                metaData.tdAttr = 'data-qtip="' + value + '"';
            }
            return value || '';
        },

        bigIntegerFormat : function(number) {
            if( isNA(number) ){
                return '-';
            }
            return Ext.util.Format.number(number, '0,000');
        },
        /**
         * format small double number, keep two digits precision
         * @param number
         * @returns {*}
         */
        smallDoubleFormatWith2Decimal : function(number) {
            if( isNA(number) ){
                return '-';
            }
            return Ext.util.Format.number(number, '0.00');
        },

        /**
         * format small double number by given pattern
         * @param number
         * @param pattern
         * @returns {*}
         */
        doubleFormatWithPattern: function(number, pattern) {
            if( isNA(number) ){
                return '-';
            }
            return Ext.util.Format.number(number, pattern);
        },

        /**
         * for big double value(display as integer and ignore decimal part, generate both hover display value and the non-hover value
         * @param value
         * @param metaData
         * @returns {*}
         */
        bigIntegerFormatRender : function(value, metaData) {
            metaData.tdAttr = 'data-qtip="' + midas.MidasUtils.bigDoubleHoverFormat(value) + '"';
            return midas.MidasUtils.bigIntegerFormat(value);
        },


        dateRenderer : function(value, metaData){
            if( isNA(value) ){
                return '-';
            }
            return Ext.Date.format(new Date(value),"d-M-Y");
        },

        // Changes the cursor to an hourglass
        cursor_wait: function () {
            document.body.style.cursor = 'wait';
        },

        // Returns the cursor to the default pointer
        cursor_clear:function () {
            document.body.style.cursor = 'default';
        },

        /**
         * check if it is a numeric
         * @param n
         * @returns {boolean}
         */
        isNumeric : function(n) {
            return !isNaN(parseFloat(n)) && isFinite(n);
        },

        /**
         * check an object is empty
         * even the number is zero, it is considered not empty since used could enter 0 in field box
         * while empty string is considered empty
         * @param object
         * @returns {boolean}
         */
        isEmpty : function(object){
            if(object == null){
                return true;
            } else if(object instanceof Date){
                return false;
            }else if(object instanceof Array){
                for(var i = 0; i < object.length; i++){
                    if(!this.isEmpty(object[i])){
                        return false;
                    }
                }
                return true;
            } else if(object instanceof Object){
                var values = Ext.Object.getValues(object);
                for(var i = 0; i < values.length; i++){
                    if(!this.isEmpty(values[i])){
                        return false;
                    }
                }
                return true;
            } else if(this.isNumeric(object)){
                return false;
            } else if(object){
                return false;
            } else {
                return true;
            }
        },

        /**
         * javascript default date could not be recognized by jackson json lib
         * @param date
         * @returns {*}
         */
        convert2JacksonCompatiableDate : function(date){
            if(date){
                if(date instanceof Date){
                    return Ext.Date.format(date, 'Y-m-d');
                } else if(typeof date === 'string' || date instanceof String){
                    return date;
                } else {
                    return null;
                }
            } else {
                return null;
            }
        },

        /**
         * remove null, undefined, "" properties
         * @param object
         * @returns {*}
         */
        removeEmptyProperties : function(object){
            if(object instanceof Array){
                for(var i = 0; i < object.length; i++){
                    this.removeEmptyProperties(object[i]);
                }
            } else if(object instanceof Object){
                for (var i in object) {
                    if (this.isEmpty(object[i])) {
                        delete object[i];
                    } else {
                        this.removeEmptyProperties(object[i]);
                    }
                }
            }
            return object;
        },

        /**
         * clear comboCmp data, load dataArray data into comboCmp, set comboCmp value to originalData
         * automatically convert string Array into object array, object like { fieldName : dataArray[i] }
         * @param comboCmp
         * @param fieldName
         * @param dataArray
         * @param originalData
         */
        updateCombo : function(comboCmp, fieldName, dataArray, originalData){
            if(comboCmp !== null && dataArray !== null && Ext.isArray(dataArray)){
                var newRecords = Ext.Array.map(dataArray, function(item, index, array){
                    var obj = {};
                    obj[fieldName] = item;
                    return obj;
                });
                comboCmp.clearValue();
                comboCmp.store.removeAll();
                comboCmp.store.loadData(newRecords);

                if(originalData !== null && Ext.Array.contains(dataArray, originalData)){
                    comboCmp.setValue(originalData);
                } else if(originalData === ''){
                    comboCmp.setValue('');
                } else if(dataArray.length > 0){
                    comboCmp.setValue(dataArray[0]);
                }
            }
        },

        /**
         * format a string, replace {0}{1}{2} with real values
         * @param array
         */
        stringFormat: function() {
            var str = arguments[0];
            for (var i = 0; i < arguments.length - 1; i++) {
                var reg = new RegExp("\\{" + i + "\\}", "gm");
                str = str.replace(reg, arguments[i + 1]);
            }
            return str;
        },

        /**
         * recursively set component and its items to isReadOnly status
         * @param cmp
         * @param isReadOnly
         */
        setReadOnly : function(cmp, isReadOnly){
            if(cmp == null) {
                return;
            } else if(cmp.xtype === 'combobox' || cmp.xtype === 'numberfield' || cmp.xtype === 'datefield' ||
                cmp.xtype === 'textareafield' || cmp.xtype === 'checkbox' || cmp.xtype === 'textfield'){
                cmp.setReadOnly(isReadOnly);
            } else if(cmp.items && cmp.items.length > 0){
                for(var i = 0; i < cmp.items.length; i++){
                    this.setReadOnly(cmp.items.items[i], isReadOnly);
                }
            }
        },

        /**
         * recursively clear component value
         * @param cmp
         */
        clearPanelData : function(cmp){
            if(cmp == null) {
                return;
            } else if(cmp.xtype === 'combobox' || cmp.xtype === 'numberfield' || cmp.xtype === 'displayfield'
                || cmp.xtype === 'datefield' || cmp.xtype === 'textareafield' || cmp.xtype === 'textfield'){
                cmp.setValue();
            } else if(cmp.xtype === 'checkbox'){
                cmp.setValue(false);
            } else if(cmp.items && cmp.items.length > 0){
                for(var i = 0; i < cmp.items.length; i++){
                    this.clearPanelData(cmp.items.items[i]);
                }
                // deal with panel header
                if(cmp.dockedItems && cmp.dockedItems.items.length > 0){
                    for(var i = 0; i < cmp.dockedItems.items.length; i++){
                        this.clearPanelData(cmp.dockedItems.items[i]);
                    }
                }
            }
        },

        /**
         * recursively set component value
         * @param cmp
         */
        setPanelData : function(cmp, data){
            if(cmp == null) {
                return;
            } else if(cmp.xtype === 'combobox' || cmp.xtype === 'numberfield' || cmp.xtype === 'displayfield'
                || cmp.xtype === 'datefield' || cmp.xtype === 'textareafield' || cmp.xtype === 'checkbox'
                || cmp.xtype === 'textfield'){
                if(cmp.key && data[cmp.key]){
                    cmp.setValue(data[cmp.key]);
                }
            } else{
                if(cmp.items && cmp.items.length > 0){
                    for(var i = 0; i < cmp.items.length; i++){
                        this.setPanelData(cmp.items.items[i], data);
                    }
                }
                // deal with panel header
                if(cmp.dockedItems && cmp.dockedItems.items.length > 0){
                    for(var i = 0; i < cmp.dockedItems.items.length; i++){
                        this.setPanelData(cmp.dockedItems.items[i], data);
                    }
                }
            }
        },

        /**
         * recursively collect component value
         * @param cmp
         */
        collectPanelData : function(cmp){
            var data = {};
            if(cmp == null) {
                return;
            } else if(cmp.xtype === 'combobox' || cmp.xtype === 'numberfield' || cmp.xtype === 'displayfield' ||
                cmp.xtype === 'datefield' || cmp.xtype === 'textareafield' || cmp.xtype === 'checkbox' || cmp.xtype === 'textfield'){
                if(cmp.key && cmp.getValue()){
                    data[cmp.key] = cmp.getValue();
                }
            } else if(cmp.items && cmp.items.length > 0){
                for(var i = 0; i < cmp.items.length; i++){
                    Ext.Object.merge(data, this.collectPanelData(cmp.items.items[i]));
                }
            }
            return data;
        },

        /**
         * remove store records which is new added
         * @param store
         */
        removeNewAddedRecords : function(store){
            if(store && store.getCount() > 0){
                var i = store.getCount() - 1;
                for (i; i >= 0; i--) {
                    if (store.getAt(i).get('isNewAdded') === true) {
                        store.removeAt(i);
                    }
                }
            }
        },

        /**
         * rollback all store data, usage for discard whole edit
         */
        rollbackRecords : function(store){
            if(store && store.getCount() > 0){
                store.each(this.rollbackRecord.bind(this));
            }
        },

        /**
         * only rollback existing record, for new added record, only apply delete
         * @param record
         */
        rollbackRecord : function(record){
            if(record !== null){
                if(record.data.changeType === this.recordState.modified){
                    var data = {};
                    Ext.Object.merge(data, record.raw);
                    data.changeType = this.recordState.editable;
                    data.isNewAdded = false;
                    record.data = data;
                } else {
                    record.data.changeType = this.recordState.editable;
                }
            }
        },

        /**
         * scale data properties by factor
         * example : scaleProperties( { a : 100, b : 1000}, 0.01, 'a', 'b') => { a : 1, b : 10}
         * @param data
         * @param factor
         * @returns {*}
         */
        scaleProperties : function(data, factor){
            if(data && factor){
                for (var i = 2; i < arguments.length; i++) {
                    if(data[arguments[i]]){
                        data[arguments[i]] *= factor;
                    }
                }
            }
            return data;
        },

        /**
         * number sort, because default sort is alphabetic
         * @param a
         * @param b
         * @returns {number}
         */
        sortNumber : function(a,b) {
            return a - b;
        },

        /**
         * calculate the monthly gap for a given month array
         * @param dates
         * @returns {Array}
         */
        calculateGaps : function(dates){
            var dateInts = [];
            var missing = [];
            for(var i = 0; i < dates.length; i++){
                dateInts.push(this.date2int(dates[i]));
            }
            dateInts = this.uniqueArray(dateInts);
            dateInts.sort(this.sortNumber);
            if(dateInts.length > 1){
                var lastIndex = dateInts.length - 1;
                var last = dateInts[lastIndex];
                var current = dateInts[lastIndex];
                while(last - current < 18 && lastIndex >= 0){
                    if(current === dateInts[lastIndex]){
                        lastIndex--;
                    } else {
                        missing.push(this.int2date(current));
                        //missing.push(current);
                    }
                    current--;
                }
                missing.reverse();
            }
            return missing;
        },

        /**
         * remove dupe elements, first sort, then if find consecutive position have same element, remove one
         * @param a
         * @returns {Array}
         */
        uniqueArray : function(a) {
            return a.sort().filter(function(item, pos, ary) {
                return !pos || item != ary[pos - 1];
            })
        },

        date2int : function(date){
            if(date instanceof Date){
                return (date.getFullYear() - 1900) * 12 + date.getMonth();
            } else if(typeof date === 'string' || date instanceof String){
                return this.date2int(new Date(date));
            }
        },

        int2date : function(integer){
            var year = integer / 12 + 1900;
            var month = integer % 12;
            return this.lastBusinessDayOfMonth(year, month);
        },

        /**
         * get last business day
         * @param year
         * @param month 0 - 11
         * @returns {*}
         */
        lastBusinessDayOfMonth : function(year, month) {
            month += 1;
            var offset = 0;
            var result = null;
            do {
                result = new Date(year, month, offset);
                offset--;
            } while (0 === result.getDay() || 6 === result.getDay());
            return result;
        }
    };
});