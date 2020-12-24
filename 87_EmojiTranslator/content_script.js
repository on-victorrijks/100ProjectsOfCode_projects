text_emoji_EN = {
    "⌚":["clock","time","timer"],
    "☕":"cofee",
    "💧": ["water","liquid"],
    "⛔": "stop",
    "🌱": ["plant","plants"],
    "🌭": ["hotdog","hotdogs"],
    "🌮": ["taco", "tacos"],
    "🌯": ["wrap","wraps"],
    "🌽": ["corn","corns"],
    "🍅": ["tomato","tomatoes"],
    "🍖": ["animal","animals"],
    "🌾":"wheat",
    "🍚":"rice",
    "🌰":"nuts",
    "🍎":["fruit","fruits"],
    "🍼":"milk",
    "🍺":"beer",
    "🍻":"beers",
    "🍷":"wine"
}

String.prototype.replaceAll = function(strReplace, strWith) {
    // See http://stackoverflow.com/a/3561711/556609
    var esc = strReplace.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
    var reg = new RegExp(esc, 'ig');
    return this.replace(reg, strWith);
};

function getWordsEmojis(){
    words = {};

    for (const emoji in text_emoji_EN) {

        const rec_words = text_emoji_EN[emoji];
        if(typeof(rec_words) == typeof([])){
            rec_words.forEach(word => {
                words[word] = emoji;
            });
        } else {
            words[rec_words] = emoji;
        }

    }

    return [words,text_emoji_EN]
}

function translate(words_emojis,isToEmojis){

    if(isToEmojis){
        temp_data = words_emojis[0];
    }

    supportedContainer_foundElement = {
        caption:[],
        h1:[],
        h2:[],
        h3:[],
        h4:[],
        h5:[],
        b:[],
        p:[],
        span:[],
        tt:[],
        i:[],
        big:[],
        small:[],
        em:[],
        strong:[],
        dfn:[],
        //code:[],
        samp:[],
        kbd:[],
        cite:[],
        abbr:[],
        acronym:[],
        sub:[],
        sup:[],
        span:[],
        a:[],
        pre:[],
        li:[],
        label:[],
        textarea:[],
        button:[],
        td:[],
        th:[],
        title: [],
        textarea: [],
    };
    
    for (const container in supportedContainer_foundElement) {

        var directTextContainer = [];
        var subContainers = document.querySelectorAll(container);

        subContainers.forEach(sContainer => {
            
            if (/<\/?[a-z][\s\S]*>/i.test(sContainer.innerHTML) == false){
                sContainer_words = sContainer.innerHTML
                sContainer_words_ar = sContainer_words.split(" ");
                temp_text = sContainer_words;
                
                for (let index = 0; index < sContainer_words_ar.length; index++) {{}
                    const html_word = sContainer_words_ar[index].toLowerCase();

                    if(temp_data[html_word] != undefined){

                        temp_text = temp_text.replaceAll(html_word, temp_data[html_word]);
                        console.log(html_word+" replaced");
                    }
                    
                }

                sContainer.innerHTML = temp_text;

            }


        });

    }

}

translate(getWordsEmojis(),true)
