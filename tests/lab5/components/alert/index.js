export class AlertComponent
{
    constructor(parent, text) {
        this.parent = parent;
        this.text = text
    }

    getHTML(){
        return(`
            <div id="alert" class="alert alert-primary" style="width:50%; margin:auto; margin-top:25px" role="alert">
            ${this.text}
            `)
    }

    render(){
        document.getElementById('mainbody').insertAdjacentHTML('beforeend',this.getHTML())
        setTimeout(()=>{document.getElementById('alert').style.display = 'none';},'1500')
    }
}