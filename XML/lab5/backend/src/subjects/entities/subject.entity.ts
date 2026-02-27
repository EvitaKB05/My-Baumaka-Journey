export class Subject {
    id: number;
    src: string;
    title: string;
    text: string;
    modules: [
        {
            src: string;
            title: string;
        }
    ];
}
